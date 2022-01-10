#include "cube_model.hpp"
#include "../model_point.hpp"
#include <iostream>

Model initCubeModel() {
    std::vector<ModelPoint> vertices;
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  -1.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  -1.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  -1.0f,  -1.0f}, std::vector<float> {1.0f,  1.0f,  0.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f, -1.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  1.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // top front left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  1.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // top front right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  1.0f,  -1.0f}, std::vector<float> {1.0f,  1.0f,  0.0f}, std::vector<float> {1.0f,  0.5f}));  // top back left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  1.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // top back right

    std::vector<int> indices;
    indices = {
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

    // Textures paths
    std::vector<const char *> texturesPaths{"../src/textures/pegue.jpg", "../src/textures/rl.png", "../src/textures/rl2.jpg"};

    // Shader paths
    const char * vertexShaderPath = "../src/shaders/vertexShaderLight.vs";
    const char * fragmentShaderPath = "../src/shaders/fragmentShaderLightSource.fs";

    return Model(vertices, indices, texturesPaths, vertexShaderPath, fragmentShaderPath);
}