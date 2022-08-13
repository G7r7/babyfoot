#include "renderer.hpp"
#include "drawing/drawer.hpp"

void Renderer::render(Scene *scene) {
    glEnable(GL_DEPTH_TEST);

    // render color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    for(GameObject &object : scene->objects) {
        object.getShader().setMat4f("transformation", glm::lookAt(object.getPosition(), object.getPosition() + object.getFront(), object.getUp()));
        object.getShader().setUniform("light", &scene->light);
        object.getShader().setUniform("camera", &scene->camera);
        this->drawer.draw(object.getModel(), object.getShader());
        //this->drawer.draw(object.getHitbox(), object.getShader());
    }
}