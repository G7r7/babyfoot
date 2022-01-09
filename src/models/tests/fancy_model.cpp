#include "fancy_model.hpp"
#include "../model_point.hpp"
#include <iostream>

FancyModel::FancyModel() {
    std::vector<ModelPoint> vertices;
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  1.0f,  0.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    vertices.push_back(ModelPoint(std::vector<float> {0.0f, 2.0f,   0.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // top
    vertices.push_back(ModelPoint(std::vector<float> {0.0f, -2.0f,   0.0f}, std::vector<float> {1.0f,  1.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // bottom
    setVertices(vertices);

    std::vector<int> indices;
    indices = {
        0, 1, 4,
        0, 2, 4,
        2, 3, 4,
        1, 3, 4,
        0, 1, 5,
        0, 2, 5,
        2, 3, 5,
        1, 3, 5
    };
    setIndices(indices);

    // Loading the texture files
    std::vector<Texture> textures;
    textures.push_back(Texture("../src/textures/pegue.jpg")); 
    textures.push_back(Texture("../src/textures/rl.png")); 
    textures.push_back(Texture("../src/textures/rl2.jpg")); 
    setTextures(textures);
}