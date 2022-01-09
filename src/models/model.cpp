#include "model.hpp"
#include <iostream>

Model::Model() {}

void Model::pushInBuffer(std::vector<float> modelPointProperty, std::vector<float>* buffer) {
    for (float modelPointPropertyValue: modelPointProperty)
        buffer->push_back(modelPointPropertyValue);
}

void Model::setVertices(std::vector<ModelPoint> points) {
    this->vertices = points;
}

void Model::setIndices(std::vector<int> indices) {
    this->indices = indices;
}

void Model::setTextures(std::vector<Texture> textures) {
    this->textures = textures;
}

std::vector<Texture> Model::getTextures() {
    return this->textures;
}

unsigned int Model::getTexturesLength() {
    return this->textures.size();
}

std::vector<float> Model::getPositions()  {
    std::vector<float> positions;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getPosition(), &positions);
    return positions;
}
unsigned int Model::getPositionsSize() {
    return getPositions().size() * sizeof(float);
}
unsigned int Model::getPositionLength() {
    return 3; // A Position is composed of 3 coordinates
}
unsigned int Model::getPositionSize() {
    return getPositionLength() * sizeof(float);
}

std::vector<float> Model::getColors()  {
    std::vector<float> colors;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getColor(), &colors);
    return colors;
}
unsigned int Model::getColorsSize() {
    return getColors().size() * sizeof(float);
}
unsigned int Model::getColorLength() {
    return 3; // A Color is composed of 3 values (rgb)
}
unsigned int Model::getColorSize() {
    return getColorLength() * sizeof(float);
}

std::vector<float> Model::getTextureCoordinates()  {
    std::vector<float> textureCoordinates;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getTextureCoordinate(), &textureCoordinates);
    return textureCoordinates;
}
unsigned int Model::getTextureCoordinatesSize() {
    return getTextureCoordinates().size() * sizeof(float);
}
unsigned int Model::getTextureCoordinateLength() {
    return 2; // A TextureCoordinate is composed of 2 coordinates
}
unsigned int Model::getTextureCoordinateSize() {
    return getTextureCoordinateLength() * sizeof(float);
}


std::vector<int> Model::getIndices() {
    return indices;
}
unsigned int Model::getIndicesSize() {
    return getIndices().size() * sizeof(int);
}
unsigned int Model::getIndiceLength() {
    return 1; // an indice is just a value
}
unsigned int Model::getIndiceSize() {
    return getIndiceLength() * sizeof(int);
}

unsigned int Model::getNbTriangles(){
    return (unsigned int) this->indices.size()/3;
}

Model::~Model() {

}