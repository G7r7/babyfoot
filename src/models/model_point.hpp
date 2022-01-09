#ifndef MPOINT_H
#define MPOINT_H

#include <vector>

class ModelPoint {
    private:
        std::vector<float> position;
        std::vector<float> textureCoordinate;
        std::vector<float> rgb;
    public:
        ModelPoint(std::vector<float> pos, std::vector<float> tex, std::vector<float> col);

        std::vector<float> getPosition();
        std::vector<float> getTextureCoordinate();
        std::vector<float> getColor();
};

#endif