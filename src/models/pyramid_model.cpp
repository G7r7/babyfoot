#include "pyramid_model.hpp"
#include "model_point.hpp"
#include <iostream>

PyramidModel::PyramidModel() {
    std::vector<ModelPoint> vertices;
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,   1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {0.0f,  1.0f})); // basis front left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,   1.0f}, std::vector<float> {0.0f,  1.0f,  0.0f}, std::vector<float> {0.0f,  0.0f}));  // basis front right
    vertices.push_back(ModelPoint(std::vector<float> {-1.0f,  0.0f,  -1.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {1.0f,  0.5f}));  // basis back left
    vertices.push_back(ModelPoint(std::vector<float> {1.0f,  0.0f,  -1.0f}, std::vector<float> {1.0f,  0.0f,  0.0f}, std::vector<float> {1.0f,  1.0f}));  // basis back right
    vertices.push_back(ModelPoint(std::vector<float> {0.0f, 1.62f,   0.0f}, std::vector<float> {0.0f,  0.0f,  1.0f}, std::vector<float> {0.0f,  0.5f}));  // top
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

    // Loading the texture files
    std::vector<Texture> textures;
    textures.push_back(Texture("../src/textures/verre-sur-mesure-granite.jpg")); 
    textures.push_back(Texture("../src/textures/rl.png")); 
    textures.push_back(Texture("../src/textures/rl2.jpg")); 
    setTextures(textures);
}