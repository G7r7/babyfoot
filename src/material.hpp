#ifndef MAT_H
#define MAT_H

#include <glm/glm.hpp>
#include <assimp/material.h>

struct Material
{   
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    Material(aiMaterial *mat);
    Material();
};

#endif