#ifndef GRAV_PROC_H
#define GRAV_PROC_H

#include "../../scene.hpp"

struct GravityProcessor {
    void process(Scene* scene, float seconds);
};

#endif