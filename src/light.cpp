#include "light.hpp"

void Light::setShaderUniform(Shader* shader, const std::string &uniform_name) {
    shader->setVec3f(uniform_name + ".position", this->position);
    shader->setVec3f(uniform_name + ".ambient", this->ambient);
    shader->setVec3f(uniform_name + ".diffuse", this->diffuse);
    shader->setVec3f(uniform_name + ".specular", this->specular);
    shader->setFloat(uniform_name + ".strength", this->strength);
}