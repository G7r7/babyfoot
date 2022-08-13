#include "camera.hpp"


Camera::Camera(float FOV, float aspect_ratio, float near_plane, float far_plane):
FOV{FOV}, aspect_ration{aspect_ratio}, near_plane{near_plane}, far_plane{far_plane} {
    position = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f,  0.0f);
} 

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(FOV), aspect_ration, near_plane, far_plane);
}

void Camera::setShaderUniform(Shader const& shader, const std::string &uniform_name) {
    shader.setVec3f(uniform_name + ".position", this->position);
    shader.setVec3f(uniform_name + ".up", this->up);
    shader.setVec3f(uniform_name + ".front", this->front);
    shader.setMat4f(uniform_name + ".view", this->getViewMatrix());
    shader.setMat4f(uniform_name + ".projection", this->getProjectionMatrix());
}