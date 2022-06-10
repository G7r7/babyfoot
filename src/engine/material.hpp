#ifndef MAT_H
#define MAT_H

#include <glm/glm.hpp>
#include <assimp/material.h>

#include "uniformable.hpp"
#include "shader.hpp"

struct Material : public Uniformable
{   
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    Material(aiMaterial *mat);
    Material();
    void setShaderUniform(Shader* shader, const std::string &uniform_name);
};

#endif