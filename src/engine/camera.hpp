#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "uniformable.hpp"

struct Camera : public Uniformable {
        Camera();
        Camera(float FOV, float aspect_ratio, float near_plane, float far_plane);
        float aspect_ration;
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        float FOV;
        float near_plane;
        float far_plane;
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        void setShaderUniform(Shader const& shader, const std::string &uniform_name) override;
};

#endif