#ifndef COLL_RES_H
#define COLL_RES_H

#include "../../../scene/object/game_object.hpp"
#include "../collision.hpp"

// Based on http://euclideanspace.com/physics/dynamics/collision/threed/rm/index.htm

struct CollisionResolver {
    void process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision);
private:
};

#endif