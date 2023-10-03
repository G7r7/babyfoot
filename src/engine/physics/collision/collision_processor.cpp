#include "collision_processor.hpp"
#include "triangle/triangle_collision.hpp"
#include <tuple>
#include <omp.h>

void CollisionProcessor::process(Scene* scene, float seconds) {
    std::vector<Collision> collisions;
    // Loop over every unique combination
    #pragma omp parallel for
    for (int i = 0; i < scene->objects.size(); i++) {
        GameObject & first = scene->objects[i];
        for (int j = i + 1; j < scene->objects.size(); j++) {
            GameObject & second = scene->objects[j];
            auto collision = checkForCollision(&first, &second);
            if (collision.has_value()) {
                collisions.push_back({
                    i,
                    j,
                    collision->point,
                    collision->surfaceNormal1,
                    collision->surfaceNormal2
                    
                });
            }
        }
    }

    for (Collision const& collision : collisions) {
        CollisionProcessor::collisionResolver.process(
            scene->objects[collision.objectIndex1],
            scene->objects[collision.objectIndex2],
            seconds,
            collision
        );
    }
}

std::optional<TriangleCollision> CollisionProcessor::checkForCollision(GameObject* object1, GameObject* object2) {
    std::vector<glm::vec3> intersections;
    std::vector<glm::vec3> surfaceNormals1;
    std::vector<glm::vec3> surfaceNormals2;
    for (auto &mesh1 : object1->getHitbox().meshes) // Every mesh of hitbox 1
    {
        for (auto &mesh2 : object2->getHitbox().meshes) // Every mesh of hitbox 2
        {
            for (size_t i = 0; i < mesh1.indices.size(); i+=3) // Every triangle of mesh 1
            {
                glm::vec3 point11 = mesh1.vertices[mesh1.indices[i+0]].Position + object1->getPosition();
                glm::vec3 point12 = mesh1.vertices[mesh1.indices[i+1]].Position + object1->getPosition();
                glm::vec3 point13 = mesh1.vertices[mesh1.indices[i+2]].Position + object1->getPosition();
                for (size_t j = 0; j < mesh2.indices.size(); j+=3) // Every triangle of mesh 2
                {
                    glm::vec3 point21 = mesh2.vertices[mesh2.indices[j+0]].Position + object2->getPosition();
                    glm::vec3 point22 = mesh2.vertices[mesh2.indices[j+1]].Position + object2->getPosition();
                    glm::vec3 point23 = mesh2.vertices[mesh2.indices[j+2]].Position + object2->getPosition();

                    glm::vec3 intersection;
                    glm::vec3 normal1;
                    glm::vec3 normal2;
                    std::optional<TriangleCollision> collision = checkForIntersection(point11, point12, point13, point21, point22, point23);
                    if(collision.has_value()) {
                        intersections.push_back(collision->point);
                        surfaceNormals1.push_back(collision->surfaceNormal1);
                        surfaceNormals2.push_back(collision->surfaceNormal2);
                    }
                }
            }
        }
    }
    if(intersections.size() > 0) {
        auto collisionPoint = CollisionProcessor::averagePoints(&intersections);
        auto surfaceNormal1 = CollisionProcessor::averageNormals(&surfaceNormals1);
        auto surfaceNormal2 = CollisionProcessor::averageNormals(&surfaceNormals2);
        return TriangleCollision{.point = collisionPoint, .surfaceNormal1 = surfaceNormal1, .surfaceNormal2 = surfaceNormal2};
    }

    return std::nullopt;
}

glm::vec3 CollisionProcessor::averagePoints(std::vector<glm::vec3>* points) {
    glm::vec3 average(0.f);
    for(glm::vec3 point : *points) {
        average += point;
    }
    return average / glm::vec3(points->size());
}

glm::vec3 CollisionProcessor::averageNormals(std::vector<glm::vec3>* normals) {
    glm::vec3 average(0.f);
    for(glm::vec3 normal : *normals) {
        average += normal;
    }
    return glm::normalize(average / glm::vec3(normals->size()));
}
