#ifndef SPEED_PROC_H
#define SPEED_PROC_H

#include "../../scene/scene.hpp"

struct SpeedProcessor {
    void process(Scene* scene, float seconds);
    static void processObject(GameObject &object, float seconds);
};

#endif