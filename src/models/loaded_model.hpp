#ifndef LOADED_M_H
#define LOADED_M_H

#include "model.hpp"

class LoadedModel {
    private:
        unsigned int *VBO, *VAO, *EBO;
    public:
        LoadedModel(Model* model);
        void Bind();
        ~LoadedModel();
};

#endif