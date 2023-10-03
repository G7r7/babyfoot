#include "collision_resolver.hpp"
#include "../../speed/speed_processor.hpp"
#include "../../rotation/rotation_processor.hpp"
#include "../collision_processor.hpp"

float CollisionResolver::smoothCollision(GameObject &object1, GameObject &object2, float seconds)
{
    SpeedProcessor::processObject(object1, -seconds);
    SpeedProcessor::processObject(object2, -seconds);
    RotationProcessor::processObject(object1, -seconds);
    RotationProcessor::processObject(object2, -seconds);
    // Number of tries to get the best precision
    int tries = 10;
    float coeff = 0.5f;
    float bestGuess = seconds;
    for (size_t i = 0; i < tries; i++)
    {
        float deltaGuess = bestGuess * coeff;
        SpeedProcessor::processObject(object1, deltaGuess);
        SpeedProcessor::processObject(object2, deltaGuess);
        RotationProcessor::processObject(object1, deltaGuess);
        RotationProcessor::processObject(object2, deltaGuess);
        auto collision = CollisionProcessor::checkForCollision(&object1, &object2);
        if (collision.has_value()) // We are colliding, we are to close, we must go back
        {
            SpeedProcessor::processObject(object1, -deltaGuess);
            SpeedProcessor::processObject(object2, -deltaGuess);
            RotationProcessor::processObject(object1, -deltaGuess);
            RotationProcessor::processObject(object2, -deltaGuess);
            coeff *= 0.5f;
        }
        else
        { // We are not colliding, we can try to get closer
            bestGuess -= deltaGuess;
        }
    }
    return bestGuess;
}

void CollisionResolver::process(GameObject &object1, GameObject &object2, float seconds, const Collision &collision) {

    float secondsAgo = this->smoothCollision(object1, object2, seconds);

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