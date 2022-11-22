#include "inertia_processor.hpp"

void InertiaProcessor::process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision) {
    if(object1.isCollisionnable() == true) {
        object1.setSpeed(glm::reflect(object1.getSpeed(), collision.surfaceNormal2));
        glm::vec3 translation = object2.getSpeed() * seconds;
        object1.move(translation);
    }
    if(object2.isCollisionnable() == true) {
        object2.setSpeed(glm::reflect(object2.getSpeed(), collision.surfaceNormal1));
        glm::vec3 translation = object2.getSpeed() * seconds;
        object2.move(translation);
    }
}