#ifndef PHYSX_PROC_H
#define PHYSX_PROC_H

#include "../scene/scene.hpp"
#include "./speed/speed_processor.hpp"
#include "./rotation/rotation_processor.hpp"
#include "./gravity/gravity_processor.hpp"
#include "./collision/collision_processor.hpp"

struct PhysicsProcessor {
    void process(Scene* scene, float seconds);
    SpeedProcessor speedProcessor;
    RotationProcessor rotationProcessor;
    GravityProcessor gravityProcessor;
    CollisionProcessor collisionProcessor;
};

#endif