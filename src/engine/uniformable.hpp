#ifndef UNIFABLE_H
#define UNIFABLE_H

#include "shader.hpp"

class Shader;

struct Uniformable
{
    virtual void setShaderUniform(Shader* shader, const std::string &uniform_name) = 0;
};


#endif