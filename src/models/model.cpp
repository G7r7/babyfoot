#include "model.hpp"
#include <iostream>

Model::Model() {}

void Model::setVertices(std::vector<ModelPoint> points) {
    this->vertices = points;
}

void Model::setIndices(std::vector<int> indices) {
    this->indices = indices;
}

std::vector<float> Model::getPositions()  {
    std::vector<float> positions;
    for (ModelPoint point : this->vertices)
        for (float coordinate : point.getPosition())
            positions.push_back(coordinate);
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
        for (float value : point.getColor())
            colors.push_back(value);
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
        for (float coordinate : point.getTextureCoordinate())
            textureCoordinates.push_back(coordinate);
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