#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Model {
    public:
        Model(){};
        virtual ~Model(){};
        virtual std::vector<float> getVertices() = 0;
        virtual std::vector<int> getIndices() = 0;
};

#endif