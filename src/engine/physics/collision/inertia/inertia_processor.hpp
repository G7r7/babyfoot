#ifndef INERT_H
#define INERT_H

#include "../../../scene/object/game_object.hpp"
#include "../collision.hpp"

struct InertiaProcessor {
    void process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision);
private:
};

#endif