#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <assimp/material.h>
#include <assimp/texture.h>

#include "uniformable.hpp"

struct Texture : Uniformable {
    Texture(const char *path, const std::string &directory, aiTextureType type);
    unsigned int id;
    aiTextureType type;
    std::string getComputedName();
    std::string path;
    std::string directory;
    void setShaderUniform(Shader const& shader, const std::string &uniform_name) override;
};

#endif