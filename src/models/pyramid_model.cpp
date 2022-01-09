#include "pyramid_model.hpp"
#include "model_point.hpp"
#include <iostream>

PyramidModel::PyramidModel() {
    std::vector<ModelPoint> vertices;
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // top left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // bottom left
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,  -1.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {1.0f,  0.5f}));  // center
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // top right
    vertices.push_back(ModelPoint(std::vector<float> {0.0f, 1.62f,   0.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // center

    setVertices(vertices);

    std::vector<int> indices;
    indices = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 4,
        0, 2, 4,
        2, 3, 4,
        1, 3, 4,
    };
    setIndices(indices);
}