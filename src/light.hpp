#ifndef LIGHT_S_H
#define LIGHT_S_H

#include "uniformable.hpp"

struct Light : public Uniformable {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 ambient = glm::vec3(0.1f);
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(1.0f);
    float strength = 0.5f;
    void setShaderUniform(Shader* shader, const std::string& uniform_name);
};

#endif