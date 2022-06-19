#ifndef COLL_PROC_H
#define COLL_PROC_H

#include "../../scene/scene.hpp"

struct CollisionProcessor {
    void process(Scene* scene);
    void process(GameObject* object1, GameObject* object2);
};

#endif