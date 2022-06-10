#include "mesh.hpp"
#include "material.hpp"

Mesh::Mesh(aiMesh* mesh, const aiScene* scene, std::string directory) : directory{directory}
{
    // Load vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex position
        glm::vec3 position; 
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z; 
        vertex.Position = position;

        // process vertex normal
        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.Normal = normal;  

        // process vertex textures coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 coordinate;
            coordinate.x = mesh->mTextureCoords[0][i].x; 
            coordinate.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = coordinate;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        this->vertices.push_back(vertex);
    }
    
    // Load indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            this->indices.push_back(face.mIndices[j]);
    }

    // Load material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        this->material = Material(material);
        
        for(unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
        {
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, i, &str);
            Texture texture(str.C_Str(), directory, aiTextureType_DIFFUSE);
            this->textures.push_back(texture);
        }
    }

    this->init();
}

void Mesh::init() {
    
    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader) 
{
    glBindTexture(GL_TEXTURE_2D, 0); // Default texture

    int a, s, d = 0;
    for(int i = 0; i < textures.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i].id); // Loaded_Texture
        glActiveTexture(GL_TEXTURE0 + i); // Texture_unit
        if(textures[i].type == aiTextureType_DIFFUSE) {
            shader.setUniform(textures[i].getComputedName() + std::to_string(d), &textures[i]);
            d++;
        }
    }
    shader.setUniform("material", &material);
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}