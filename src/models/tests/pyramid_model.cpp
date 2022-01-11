#include "pyramid_model.hpp"
#include "../model_point.hpp"
#include <iostream>

Model initPyramidModel() {
    std::vector<ModelPoint> distinctVertices;
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,  -1.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    distinctVertices.push_back(ModelPoint(std::vector<float> {0.0f, 1.62f,   0.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // top

    std::vector<int> indices;
    indices = {
        0, 1, 2,
        1, 3, 2,
        0, 1, 4,
        0, 4, 2,
        2, 4, 3,
        1, 3, 4,
    };

    std::vector<ModelPoint> vertices;
    for (int i : indices)
        vertices.push_back(distinctVertices[i]);

    // Textures paths
    const char * texturePath = "../src/textures/rl.png";

    // Shader paths
    const char * vertexShaderPath = "../src/shaders/vertexShaderMatrix.vs";
    const char * fragmentShaderPath = "../src/shaders/fragmentShaderTextureMultiple.fs";

    return Model(vertices, texturePath, vertexShaderPath, fragmentShaderPath);
}