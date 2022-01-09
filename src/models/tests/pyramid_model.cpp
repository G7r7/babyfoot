#include "pyramid_model.hpp"
#include "../model_point.hpp"
#include <iostream>

Model initPyramidModel() {
    std::vector<ModelPoint> vertices;
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,  -1.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    vertices.push_back(ModelPoint(std::vector<float> {0.0f, 1.62f,   0.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // top

    std::vector<int> indices;
    indices = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 4,
        0, 2, 4,
        2, 3, 4,
        1, 3, 4,
    };

    // Textures paths
    std::vector<const char *> texturesPaths{"../src/textures/pegue.jpg", "../src/textures/rl.png", "../src/textures/rl2.jpg"};

    // Shader paths
    std::vector<const char *> shaderPaths{"../src/shaders/vertexShaderMatrix.vs", "../src/shaders/fragmentShaderTextureMultiple.fs"};

    // Shader paths
    const char * vertexShaderPath = "../src/shaders/vertexShaderMatrix.vs";
    const char * fragmentShaderPath = "../src/shaders/fragmentShaderTextureMultiple.fs";

    return Model(vertices, indices, texturesPaths, vertexShaderPath, fragmentShaderPath);
}