#include "texture.hpp"
#include "../stb_image.h"

Texture::Texture(char* path) {
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path, &width, &height, &nbChannels, 0); 
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

int Texture::getNbChannels() {
    return nbChannels;
}

unsigned char* Texture::getData() {
    return data;
}

Texture::~Texture() {
    // stbi_image_free(data);
}