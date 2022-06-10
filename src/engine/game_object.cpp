#include "game_object.hpp"

GameObject::GameObject(Model model, Shader shader) :
model{model}, shader{shader} {
    this->position = glm::vec3(0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);

    this->isGlowing = false;
}

glm::mat4 GameObject::getTransformationMatrix() {
    return glm::lookAt(position, position + front, up);
}

void GameObject::updateTransformationUniform() {
    shader.setMat4f("transformation", getTransformationMatrix());
}

void GameObject::setLighting(Light* light) {
    shader.setUniform("light", light);
}

void GameObject::setCamera(Camera* camera) {
    shader.setUniform("camera", camera);
}

void GameObject::draw() {
    model.Draw(shader);
}

void GameObject::glow() {
    isGlowing = !isGlowing;
    shader.setBool("glowing", isGlowing);
}

void GameObject::move(glm::vec3 vector) {
    position += vector;
}