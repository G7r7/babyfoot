#ifndef COLL_PROC_H
#define COLL_PROC_H

#include "../../scene/scene.hpp"

struct CollisionProcessor {
    void process(Scene* scene, float seconds);
    void process(GameObject* object1, GameObject* object2, float seconds);
};

#endif