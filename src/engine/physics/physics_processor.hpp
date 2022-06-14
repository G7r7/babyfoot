#ifndef PHYSX_PROC_H
#define PHYSX_PROC_H

#include "../scene.hpp"
#include "./gravity/gravity_processor.hpp"

struct PhysicsProcessor {
    void process(Scene* scene, float seconds);
    GravityProcessor gravityProcessor;
};

#endif