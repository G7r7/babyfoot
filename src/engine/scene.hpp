#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "game_object.hpp"
#include "light.hpp"
#include "camera.hpp"

struct Scene {
    Scene(Camera camera, Light light, std::vector<GameObject> objects, glm::vec3 gravity);
    std::vector<GameObject> objects;
    Light light;
    Camera camera;
    glm::vec3 gravity;
    void render();
};

#endif