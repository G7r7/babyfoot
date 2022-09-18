#include "speed_processor.hpp"

void SpeedProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        glm::vec3 translation = object.getSpeed() * seconds;
        object.move(translation);
    }
}