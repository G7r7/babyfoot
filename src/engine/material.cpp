#include "material.hpp"

Material::Material(aiMaterial *mat)
{
    aiColor3D color(0.f, 0.f, 0.f);
    float shininess;

    mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    this->diffuse = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
    this->ambient = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
    this->specular = glm::vec3(color.r, color.g, color.b);

    mat->Get(AI_MATKEY_SHININESS, this->shininess);
}

Material::Material() {}

void Material::setShaderUniform(Shader* shader, const std::string &uniform_name) {
    shader->setFloat(uniform_name + ".shininess", this->shininess);
    shader->setVec3f(uniform_name + ".ambient", this->ambient);
    shader->setVec3f(uniform_name + ".diffuse", this->diffuse);
    shader->setVec3f(uniform_name + ".specular", this->specular);
}