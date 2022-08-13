#include "drawer.hpp"

void Drawer::draw(Model const& model, Shader const& shader)
{   
    for(Mesh const& mesh : model.meshes) {
        glBindTexture(GL_TEXTURE_2D, 0); // Default texture

        int a, s, d = 0;
        for(int i = 0; i < mesh.textures.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id); // Loaded_Texture
            glActiveTexture(GL_TEXTURE0 + i); // Texture_unit
            if(mesh.textures[i].type == aiTextureType_DIFFUSE) {
                shader.setUniform(mesh.textures[i].getComputedName() + std::to_string(d), &mesh.textures[i]);
                d++;
            }
        }
        shader.setUniform("material", &mesh.material);
        
        // draw mesh
        glBindVertexArray(mesh.VAO);
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // Wireframe mode
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
}