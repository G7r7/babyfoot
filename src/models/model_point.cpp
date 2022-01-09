#include "model_point.hpp"

ModelPoint::ModelPoint(std::vector<float> pos, std::vector<float> tex, std::vector<float> col) {
    position = pos;
    textureCoordinate = tex;
    rgb = col;
}

std::vector<float> ModelPoint::getPosition() {
    return position;
}

std::vector<float> ModelPoint::getTextureCoordinate() {
    return textureCoordinate;
}

std::vector<float> ModelPoint::getColor() {
    return rgb;
}
