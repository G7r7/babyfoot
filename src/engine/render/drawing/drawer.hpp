#ifndef DRAWER_H
#define DRAWER_H

#include "../../model.hpp"
#include "../../shader.hpp"

struct Drawer {
    void draw(Model &model, Shader &shader);
};

#endif