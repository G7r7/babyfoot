#include "gravity_processor.hpp"

void GravityProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        if(object.isGravitable() == true) {
            object.setSpeed(object.getSpeed() + scene->gravity * seconds);
            glm::vec3 translation = object.getSpeed() * seconds;
            object.move(translation);
        }
    }
}