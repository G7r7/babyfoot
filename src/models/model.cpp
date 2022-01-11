#include "model.hpp"
#include <iostream>

Model::Model(std::vector<ModelPoint> points, const char* texturePath, const char * vertexShaderPath, const char * fragmentShaderPath) :
    vertices(points), texturePath(texturePath), vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath) {}

unsigned int Model::getVerticesNb() { return this->vertices.size(); };

unsigned int Model::getPositionsSize() { return getPositions().size() * sizeof(float); }
unsigned int Model::getPositionLength() { return 3; } // A Position is composed of 3 coordinates
unsigned int Model::getPositionSize() { return getPositionLength() * sizeof(float); }

unsigned int Model::getColorsSize() { return getColors().size() * sizeof(float); }
unsigned int Model::getColorLength() { return 3; } // A Color is composed of 3 values (rgb)
unsigned int Model::getColorSize() { return getColorLength() * sizeof(float); }

unsigned int Model::getTextureCoordinatesSize() { return getTextureCoordinates().size() * sizeof(float); }
unsigned int Model::getTextureCoordinateLength() { return 2; } // A TextureCoordinate is composed of 2 coordinates
unsigned int Model::getTextureCoordinateSize() { return getTextureCoordinateLength() * sizeof(float); }

unsigned int Model::getNormalsSize() { return getNormals().size() * sizeof(float); }
unsigned int Model::getNormalLength() { return 3; } // an normal is just a value
unsigned int Model::getNormalSize() { return getNormalLength() * sizeof(float); }

const char * Model::getTexturePath() { return this->texturePath; }
const char * Model::getVertexShaderPath() { return this->vertexShaderPath; }
const char * Model::getFragmentShaderPath() { return this->fragmentShaderPath; }

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

std::vector<float> Model::getNormals() {
    std::vector<float> normals;
    for (int i = 0; i < this->vertices.size(); i++) {
        if (i % 3 == 0) {
            glm::vec3 dir1(
                vertices[i].getPosition()[0] - vertices[i+1].getPosition()[0], 
                vertices[i].getPosition()[1] - vertices[i+1].getPosition()[1], 
                vertices[i].getPosition()[2] - vertices[i+1].getPosition()[2]
            );
            glm::vec3 dir2(
                vertices[i+1].getPosition()[0] - vertices[i+2].getPosition()[0], 
                vertices[i+1].getPosition()[1] - vertices[i+2].getPosition()[1], 
                vertices[i+1].getPosition()[2] - vertices[i+2].getPosition()[2]
            );
            glm::vec3 normal = glm::cross(dir1, dir2);
            for (size_t i = 0; i < 3; i++) {
                normals.push_back(normal[0]);
                normals.push_back(normal[1]);
                normals.push_back(normal[2]);
            }
        } else {
            continue;
        }
    }
    return normals;
}

void Model::pushInBuffer(std::vector<float> modelPointProperty, std::vector<float>* buffer) {
    for (float modelPointPropertyValue: modelPointProperty)
        buffer->push_back(modelPointPropertyValue);
}

Model::~Model() {

}