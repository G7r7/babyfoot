#include "collision_resolver.hpp"

void CollisionResolver::process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision) {
    // if(object1.isCollisionnable() == true) {
    //     object1.setSpeed(glm::reflect(object1.getSpeed(), collision.surfaceNormal2));
    //     glm::vec3 translation = object2.getSpeed() * seconds;
    //     object1.move(translation);
    // }
    // if(object2.isCollisionnable() == true) {
    //     object2.setSpeed(glm::reflect(object2.getSpeed(), collision.surfaceNormal1));
    //     glm::vec3 translation = object2.getSpeed() * seconds;
    //     object2.move(translation);
    // }
    Collision localCollision1 = collision.getTransformed(object1.getTransformationMatrix());
    Collision localCollision2 = collision.getTransformed(object2.getTransformationMatrix());
    glm::vec3 axis1 = glm::normalize(localCollision1.point - object1.getPosition());
    glm::vec3 axis2 = glm::normalize(localCollision2.point - object2.getPosition());
    // float moment1 = object1.getMomentOfIntertia(axis1, )
}