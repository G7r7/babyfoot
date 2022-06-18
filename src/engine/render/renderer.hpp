#ifndef RENDERER_H
#define RENDERER_H

#include "../scene/scene.hpp"
#include "drawing/drawer.hpp"

struct Renderer {
    Drawer drawer;
    void render(Scene *scene);
};

#endif