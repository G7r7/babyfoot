#ifndef COLL_PROC_H
#define COLL_PROC_H

#include "../../scene/scene.hpp"
#include "inertia/inertia_processor.hpp"

struct CollisionProcessor {
    InertiaProcessor inertiaProcessor;
    void process(Scene* scene, float seconds);
private:
    bool checkForCollision(GameObject* object1, GameObject* object2, float seconds,
        glm::vec3* collisionPoint, glm::vec3* surfaceNormal1, glm::vec3* surfaceNormal2);
    glm::vec3 averagePoints(std::vector<glm::vec3>* points);
    glm::vec3 averageNormals(std::vector<glm::vec3>* normals);
};

#endif