#ifndef LOADED_M_H
#define LOADED_M_H

#include "model.hpp"
#include "../shader.hpp"

class LoadedModel {
    private:
        unsigned int indicesNb;
        std::vector<Texture> texturesData;
        Shader shader;
        unsigned int *VBO, *VAO, *EBO, *textures;
    public:
        LoadedModel(Model* model);
        void bind();
        void setShaderFloat(const char * name, float value);
        void setShaderInt(const char * name, int value);
        void setShaderBool(const char * name, bool value);
        void setShaderMat4f(const char * name, glm::mat4 value);
        void setShaderVec3f(const char * name, glm::vec3 value);
        void draw();
        ~LoadedModel();
};

#endif