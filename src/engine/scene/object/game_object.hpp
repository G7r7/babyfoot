#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "../../../engine/model.hpp"
#include "../../../engine/shader.hpp"
#include "../../../engine/light.hpp"
#include "../../../engine/camera.hpp"
struct GameObject {
    GameObject(Model model, Shader shader);
    Model model;
    Shader shader;
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;

    bool isGlowing;
    void glow();
    void move(glm::vec3 vector);
    glm::vec3 speed;
    bool fixed;
};

#endif