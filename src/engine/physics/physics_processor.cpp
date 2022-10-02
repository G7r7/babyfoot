#include "physics_processor.hpp"

void PhysicsProcessor::process(Scene* scene, float seconds) {
    gravityProcessor.process(scene, seconds);
    collisionProcessor.process(scene, seconds);
    speedProcessor.process(scene, seconds);
    rotationProcessor.process(scene, seconds);
}