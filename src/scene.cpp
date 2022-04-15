#include "scene.hpp"

Scene::Scene() {}

void Scene::render() {
    for(auto object : objects) {
        object.updateTransformationUniform();
        object.setCamera(camera);
        object.setLighting(light);
        object.draw();
    }
}