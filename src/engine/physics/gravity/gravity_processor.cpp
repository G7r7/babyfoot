#include "gravity_processor.hpp"

void GravityProcessor::process(Scene* scene, float seconds) {
    for(auto &object : scene->objects) {
        if(object.fixed != true) {
            object.speed += scene->gravity*seconds;
            glm::vec3 translation = object.speed*seconds;
            object.move(translation);
        }
    }
}