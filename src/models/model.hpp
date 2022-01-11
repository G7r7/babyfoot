#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include <vector>
#include "model.hpp"
#include "model_point.hpp"
#include "texture.hpp"
#include "../shader.hpp"

class Model
{
    private:
        std::vector<ModelPoint> vertices;
        std::vector<int> indices;
        const char* texturePath;
        const char* vertexShaderPath;
        const char* fragmentShaderPath;
        void pushInBuffer(std::vector<float>, std::vector<float>*);

    public:
        Model(std::vector<ModelPoint> points, std::vector<int> indices, const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Model();

        std::vector<float> getPositions();
        unsigned int getPositionsSize();
        unsigned int getPositionSize();
        unsigned int getPositionLength();

        std::vector<float> getColors();
        unsigned int getColorsSize();
        unsigned int getColorSize();
        unsigned int getColorLength();

        std::vector<float> getTextureCoordinates();
        unsigned int getTextureCoordinatesSize();
        unsigned int getTextureCoordinateSize();
        unsigned int getTextureCoordinateLength();

        std::vector<int> getIndices();
        unsigned int getIndicesSize();
        unsigned int getIndiceSize();
        unsigned int getIndiceLength();

        const char* getTexturePath();
        const char * getVertexShaderPath();
        const char * getFragmentShaderPath();
        
        unsigned int getNbTriangles();
};

#endif