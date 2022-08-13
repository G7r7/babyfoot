
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include "shader.hpp"
#include "material.hpp"
#include "texture.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
    public:
        Mesh(aiMesh* mesh, const aiScene* scene, std::string directory);
        // TODO: Refactor (put members in private and create appropriate getters/setter) and forget about 'mutable'
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> mutable     textures;
        Material             mutable     material;

        std::string               directory;

        unsigned int VAO, VBO, EBO;
    private:
        void init();
}; 

#endif