#include "collision_resolver.hpp"

void CollisionResolver::process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision) {

    glm::vec3 radius1 = collision.point - object1.getPosition();
    glm::vec3 radius2 = collision.point - object2.getPosition();
    
    // We use the normal pointing away from object1
    const auto &normal = collision.surfaceNormal1;
    
    // Bodies velocities at contact point
    const auto v1 = object1.getSpeed() + (object1.getRotationSpeed() * radius1);
    const auto v2 = object2.getSpeed() + (object2.getRotationSpeed() * radius2);

    // Precollision relative velocity
    const auto relativeVelocity = v2 - v1;

    // Define how much energy is restitued after collison (1.0 = all energy)
    const float restitutionCoefficient = .5f;

    // We compute the reaction impulse magnitude
    const auto reactionImpulseMagnitude = 
        glm::dot(-(1.0f+restitutionCoefficient) * relativeVelocity, normal)/
        (
            1/object1.getMass()+
            1/object2.getMass()+
            glm::dot(
                glm::cross(glm::inverse(object1.getMomentOfInertiaTensor()) * glm::cross(radius1,normal), radius1)+
                glm::cross(glm::inverse(object2.getMomentOfInertiaTensor()) * glm::cross(radius2,normal), radius2),
                normal
            )
        );
    
    // We compute the reaction impulse vector
    const auto reactionImpulseVector = reactionImpulseMagnitude * normal;

    // We compute the new linear velocities
    const auto newV1 = v1 - (reactionImpulseVector/object1.getMass());
    const auto newV2 = v2 + (reactionImpulseVector/object2.getMass());

    // We compute the new angular velocities
    const auto newA1 = object1.getRotationSpeed()-
        reactionImpulseMagnitude * glm::inverse(object1.getMomentOfInertiaTensor()) * glm::cross(radius1,normal);
    const auto newA2 = object2.getRotationSpeed()+
        reactionImpulseMagnitude * glm::inverse(object2.getMomentOfInertiaTensor()) * glm::cross(radius2,normal);

    // We apply the newly calculated speeds to the objects
    object1.setSpeed(newV1);
    object2.setSpeed(newV2);
    object1.setRotationSpeed(newA1);
    object2.setRotationSpeed(newA2);

    // We make the objects travel a bit to avoid infinite collision loop
    glm::vec3 translation1 = object1.getSpeed() * seconds;
    glm::vec3 translation2 = object2.getSpeed() * seconds;
    object1.move(translation1);
    object2.move(translation2);
}