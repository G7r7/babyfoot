#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "uniformable.hpp"

class Uniformable;

class Shader
{
public:
    unsigned int ID; // Program (shader) ID
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setMat4f(const std::string &name, glm::mat4 value);
    void setVec3f(const std::string &name, glm::vec3 value);
    void setUniform(const std::string &name, Uniformable* value);
};

#endif