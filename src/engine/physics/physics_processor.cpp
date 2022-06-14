#include "physics_processor.hpp"

void PhysicsProcessor::process(Scene* scene, float seconds) {
    gravityProcessor.process(scene, seconds);
}