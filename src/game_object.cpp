#include "game_object.hpp"

GameObject::GameObject(Model model, Shader shader, glm::vec3 position, glm::vec3 up, glm::vec3 front) :
model{model}, shader{shader}, position{position}, up{up}, front{front} {}

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