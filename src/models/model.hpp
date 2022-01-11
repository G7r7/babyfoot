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
        const char* texturePath;
        const char* vertexShaderPath;
        const char* fragmentShaderPath;
        void pushInBuffer(std::vector<float>, std::vector<float>*);

    public:
        Model(std::vector<ModelPoint> points, const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath);
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

        std::vector<float> getNormals();
        unsigned int getNormalsSize();
        unsigned int getNormalSize();
        unsigned int getNormalLength();

        const char* getTexturePath();
        const char * getVertexShaderPath();
        const char * getFragmentShaderPath();
        
        unsigned int getVerticesNb();
};

#endif