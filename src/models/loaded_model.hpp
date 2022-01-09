#ifndef LOADED_M_H
#define LOADED_M_H

#include "model.hpp"
#include "../shader.hpp"

class LoadedModel {
    private:
        std::vector<Texture> texturesData;
        Shader shader;
        unsigned int *VBO, *VAO, *EBO, *textures;
    public:
        LoadedModel(Model* model);
        void bind();
        void setShaderFloat(const char * name, float value) { this->shader.setFloat(name, value); };
        void setShaderInt(const char * name, int value) { this->shader.setInt(name, value); };
        void setShaderBool(const char * name, bool value) { this->shader.setBool(name, value); };
        void setShaderMat4f(const char * name, glm::mat4 value) { this->shader.setMat4f(name, value); };
        ~LoadedModel();
};

#endif