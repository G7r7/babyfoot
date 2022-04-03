
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include "shader.hpp"
#include "material.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        Mesh(aiMesh* mesh, const aiScene* scene);

        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;
        Material                  material;

        void Draw(Shader &shader);
    private:
        unsigned int VAO, VBO, EBO;
        void init();
}; 

#endif