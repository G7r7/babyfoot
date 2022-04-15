#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "model.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "camera.hpp"
struct GameObject {
    GameObject(Model model, Shader shader, glm::vec3 position, glm::vec3 up, glm::vec3 front);
    Model model;
    Shader shader;
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::mat4 getTransformationMatrix();
    void updateTransformationUniform();
    void setLighting(Light* light);
    void setCamera(Camera* camera);
    void draw();
};

#endif