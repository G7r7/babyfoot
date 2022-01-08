#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Model {
    public:
        Model(){};
        virtual ~Model(){};
        virtual std::vector<float> getVertices() = 0;
        virtual std::vector<int> getIndices() = 0;
        virtual unsigned int getVerticesSize() = 0;
        virtual unsigned int getIndicesSize() = 0;
};

#endif