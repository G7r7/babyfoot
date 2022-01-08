#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include <vector>
#include "model.hpp"

class PyramidModel : public Model
{
    private:
        std::vector<float> vertices;
        std::vector<int> indices;
    public:
        PyramidModel();
        std::vector<float> getVertices() override;
        std::vector<int> getIndices() override;
        unsigned int getVerticesSize() override;
        unsigned int getIndicesSize() override;
        ~PyramidModel();
};

#endif