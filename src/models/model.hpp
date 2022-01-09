#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include <vector>
#include "model.hpp"
#include "model_point.hpp"

class Model
{
    private:
        std::vector<ModelPoint> vertices;
        std::vector<int> indices;
    public:
        Model();
        
        void setVertices(std::vector<ModelPoint>);
        void setIndices(std::vector<int>);

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
};

#endif