#include "rotation_processor.hpp"

void RotationProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        this->processObject(object, seconds);
    }
}

void RotationProcessor::processObject(GameObject& object, float seconds) {
    glm::quat rotatedX = glm::rotate(object.getOrientation(), object.getRotationSpeed().x * seconds, glm::vec3(1, 0, 0));
    glm::quat rotatedXY = glm::rotate(rotatedX, object.getRotationSpeed().y * seconds, glm::vec3(0, 1, 0));
    glm::quat rotatedXYZ = glm::rotate(rotatedXY, object.getRotationSpeed().z * seconds, glm::vec3(0, 0, 1));
    object.setOrientation(rotatedXYZ);
}