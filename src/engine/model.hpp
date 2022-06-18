#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "shader.hpp"

class Model 
{
    public:
        Model(std::string path);
        std::vector<Mesh> meshes;
    private:
        std::string directory;

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif