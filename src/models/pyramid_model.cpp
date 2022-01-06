#include "pyramid_model.hpp"

PyramidModel::PyramidModel(): 
    vertices{
        // positions
        -1.0f,  0.0f,   1.0f,  // top left
         1.0f,  0.0f,   1.0f,  // bottom left
        -1.0f,  0.0f,  -1.0f,  // center
         1.0f,  0.0f,  -1.0f,  // top right
         0.0f, 1.62f,   0.0f,  // center
    }, indices{
        0, 1, 2,
        1, 2, 3,
        0, 1, 4,
        0, 2, 4,
        2, 3, 4,
        1, 3, 4,
    }
{}

std::vector<float> PyramidModel::getVertices()  {
    return vertices;
}

std::vector<int> PyramidModel::getIndices() {
    return indices;
}

PyramidModel::~PyramidModel()
{

}
