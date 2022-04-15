#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "game_object.hpp"
#include "light.hpp"
#include "camera.hpp"

struct Scene {
    Scene();
    std::vector<GameObject> objects;
    Light* light;
    Camera* camera;
    void render();
};

#endif