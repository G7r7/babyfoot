#ifndef COLL_PROC_H
#define COLL_PROC_H

#include "../../scene/scene.hpp"
#include "resolver/collision_resolver.hpp"
#include <optional>
#include "triangle/triangle_collision.hpp"

struct CollisionProcessor {
    CollisionResolver collisionResolver;
    void process(Scene* scene, float seconds);
private:
    std::optional<TriangleCollision> checkForCollision(GameObject* object1, GameObject* object2, float seconds);
    glm::vec3 averagePoints(std::vector<glm::vec3>* points);
    glm::vec3 averageNormals(std::vector<glm::vec3>* normals);
};

#endif