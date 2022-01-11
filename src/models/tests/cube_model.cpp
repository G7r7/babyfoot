#include "cube_model.hpp"
#include "../model_point.hpp"
#include <iostream>

Model initCubeModel() {
    std::vector<ModelPoint> distinctVertices;
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  -1.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f,  -1.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  -1.0f,  -1.0f}, std::vector<float> {1.0f,  1.0f,  0.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f, -1.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  1.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // top front left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f,  1.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // top front right
    distinctVertices.push_back(ModelPoint(std::vector<float> {-1.0f,  1.0f,  -1.0f}, std::vector<float> {1.0f,  1.0f,  0.0f}, std::vector<float> {1.0f,  0.5f}));  // top back left
    distinctVertices.push_back(ModelPoint(std::vector<float> {1.0f,  1.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // top back right

    std::vector<int> indices = {
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        2, 3, 6,
        3, 6, 7,

        0, 1, 4,
        1, 4, 5,

        0, 2, 4,
        2, 4, 6,

        1, 3, 5,
        3, 5, 7
    };

    std::vector<ModelPoint> vertices;
    for (int i : indices)
        vertices.push_back(distinctVertices[i]);

    // Textures paths
    const char * texturePath = "../src/textures/pegue.jpg";

    // Shader paths
    const char * vertexShaderPath = "../src/shaders/vertexShaderLightSource.vs";
    const char * fragmentShaderPath = "../src/shaders/fragmentShaderLightSource.fs";

    return Model(vertices, texturePath, vertexShaderPath, fragmentShaderPath);
}