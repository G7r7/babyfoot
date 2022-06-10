#include "scene.hpp"

Scene::Scene(Camera camera,Light light, std::vector<GameObject> objects):camera{camera},light{light},objects{objects}{}

void Scene::render() {
    for(auto object : objects) {
        object.updateTransformationUniform();
        object.setCamera(&camera);
        object.setLighting(&light);
        object.draw();
    }
}