#include "game_object.hpp"

GameObject::GameObject(Model model, Shader shader, Model hitbox):
    _model{model}, _shader{shader}, _hitbox{hitbox} {}

GameObject::GameObject(Model model, Shader shader):
    GameObject::GameObject(model, shader, model) {}


void GameObject::toggleGlow() {
    _isGlowing = !_isGlowing;
    _shader.setBool("glowing", _isGlowing);
}

void GameObject::move(glm::vec3 vector) {
    _position += vector;
}