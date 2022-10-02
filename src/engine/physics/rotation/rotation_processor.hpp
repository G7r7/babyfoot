#ifndef ROT_PROC_H
#define ROT_PROC_H

#include "../../scene/scene.hpp"

struct RotationProcessor {
    void process(Scene* scene, float seconds);
};

#endif