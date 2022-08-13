#ifndef UNIFABLE_H
#define UNIFABLE_H

#include "shader.hpp"

class Shader;

class Uniformable
{
public:
    virtual void setShaderUniform(Shader const& shader, const std::string &uniform_name) = 0;
};


#endif