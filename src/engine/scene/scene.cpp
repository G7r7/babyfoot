#include "scene.hpp"

Scene::Scene(Camera camera,Light light, std::vector<GameObject> objects, glm::vec3 gravity):camera{camera},light{light},objects{objects},gravity{gravity}{}