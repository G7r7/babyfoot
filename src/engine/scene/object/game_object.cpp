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

glm::mat4 GameObject::getTransformationMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 angles = glm::eulerAngles(this->getOrientation());
    model = glm::translate(model, this->getPosition());
    model = glm::rotate(model, angles.x, glm::vec3(1,0,0));
    model = glm::rotate(model, angles.y, glm::vec3(0,1,0));
    model = glm::rotate(model, angles.z, glm::vec3(0,0,1));
    return model;
}

float GameObject::getMomentOfInertia(glm::vec3 axis, glm::vec3 point) const {
    // Here we approximate our object as a solid sphere (I = 2/5 * m * r²)
    return 0.4 * _mass * pow(glm::distance(point, glm::vec3(0.f)), 2);
}

float GameObject::getKineticEnergy() const {
    return 0.5 * _mass * pow(glm::length(getSpeed()),2);
}