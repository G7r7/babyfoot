#include "game_object.hpp"

GameObject::GameObject(Model model, Shader shader) :
model{model}, shader{shader}, hitbox{model} {
    this->position = glm::vec3(0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->speed = glm::vec3(0.0f);
    this->fixed = false;
    this->isGlowing = false;
}

void GameObject::glow() {
    isGlowing = !isGlowing;
    shader.setBool("glowing", isGlowing);
}

void GameObject::move(glm::vec3 vector) {
    position += vector;
}