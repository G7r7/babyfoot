#ifndef DRAWER_H
#define DRAWER_H

#include "../../model.hpp"
#include "../../shader.hpp"

struct Drawer {
    void draw(Model const& model, Shader const& shader);
};

#endif