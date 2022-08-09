#include "gravity_processor.hpp"

void GravityProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        if(object.gravitable == true) {
            object.speed += scene->gravity*seconds;
            glm::vec3 translation = object.speed*seconds;
            object.move(translation);
        }
    }
}