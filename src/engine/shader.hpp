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
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4f(const std::string &name, glm::mat4 value) const;
    void setVec3f(const std::string &name, glm::vec3 value) const;
    void setUniform(const std::string &name, Uniformable* value) const;

private:
    // use/activate shader
    void use() const;

    unsigned int _id; // Program (shader) ID

};

#endif