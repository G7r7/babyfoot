#include "model.hpp"
#include <iostream>

Model::Model(std::vector<ModelPoint> points, std::vector<int> indices, const char* texturePath, const char * vertexShaderPath, const char * fragmentShaderPath) :
    vertices(points), indices(indices), texturePath(texturePath), vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath) {}

unsigned int Model::getPositionsSize() { return getPositions().size() * sizeof(float); }
unsigned int Model::getPositionLength() { return 3; } // A Position is composed of 3 coordinates
unsigned int Model::getPositionSize() { return getPositionLength() * sizeof(float); }

unsigned int Model::getColorsSize() { return getColors().size() * sizeof(float); }
unsigned int Model::getColorLength() { return 3; } // A Color is composed of 3 values (rgb)
unsigned int Model::getColorSize() { return getColorLength() * sizeof(float); }

unsigned int Model::getTextureCoordinatesSize() { return getTextureCoordinates().size() * sizeof(float); }
unsigned int Model::getTextureCoordinateLength() { return 2; } // A TextureCoordinate is composed of 2 coordinates
unsigned int Model::getTextureCoordinateSize() { return getTextureCoordinateLength() * sizeof(float); }

unsigned int Model::getIndicesSize() { return getIndices().size() * sizeof(int); }
unsigned int Model::getIndiceLength() { return 1; } // an indice is just a value
unsigned int Model::getIndiceSize() { return getIndiceLength() * sizeof(int); }

unsigned int Model::getNbTriangles(){ return (unsigned int) this->indices.size()/3; }

const char * Model::getTexturePath() { return this->texturePath; }
const char * Model::getVertexShaderPath() { return this->vertexShaderPath; }
const char * Model::getFragmentShaderPath() { return this->fragmentShaderPath; }

std::vector<int> Model::getIndices() { return indices; }

std::vector<float> Model::getPositions()  {
    std::vector<float> positions;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getPosition(), &positions);
    return positions;
}

std::vector<float> Model::getColors()  {
    std::vector<float> colors;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getColor(), &colors);
    return colors;
}

std::vector<float> Model::getTextureCoordinates()  {
    std::vector<float> textureCoordinates;
    for (ModelPoint point : this->vertices)
        pushInBuffer(point.getTextureCoordinate(), &textureCoordinates);
    return textureCoordinates;
}

void Model::pushInBuffer(std::vector<float> modelPointProperty, std::vector<float>* buffer) {
    for (float modelPointPropertyValue: modelPointProperty)
        buffer->push_back(modelPointPropertyValue);
}

Model::~Model() {

}