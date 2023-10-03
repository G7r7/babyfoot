#include "speed_processor.hpp"

void SpeedProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        this->processObject(object, seconds);
    }
}

void SpeedProcessor::processObject(GameObject &object, float seconds) {
    glm::vec3 translation = object.getSpeed() * seconds;
    object.move(translation);
}
