#include "collision_processor.hpp"
#include "triangle/triangle_collision.hpp"
#include <tuple>
#include <omp.h>


struct Collision {
    int objectIndex1;
    int objectIndex2;
    glm::vec3 point;
    glm::vec3 surfaceNormal1;
    glm::vec3 surfaceNormal2;
};

void CollisionProcessor::process(Scene* scene, float seconds) {
    std::vector<Collision> collisions;
    // Loop over every unique combination
    #pragma omp parallel for
    for (int i = 0; i < scene->objects.size(); i++) {
        GameObject & first = scene->objects[i];
        for (int j = i + 1; j < scene->objects.size(); j++) {
            GameObject & second = scene->objects[j];
            glm::vec3 collisionPoint, surfaceNormal1, surfaceNormal2;
            bool collides = process(&first, &second, seconds, &collisionPoint, &surfaceNormal1, &surfaceNormal2);
            if (collides) {
                Collision collision = {
                    i,
                    j,
                    collisionPoint,
                    surfaceNormal1,
                    surfaceNormal2
                };
                collisions.push_back(collision);
            }
        }
    }

    for (Collision const& collision : collisions) {
        if(scene->objects[collision.objectIndex1].isCollisionnable() == true) {
            scene->objects[collision.objectIndex1].setSpeed(glm::reflect(scene->objects[collision.objectIndex1].getSpeed(), collision.surfaceNormal2));
            glm::vec3 translation = scene->objects[collision.objectIndex2].getSpeed() * seconds;
            scene->objects[collision.objectIndex1].move(translation);
        }
        if(scene->objects[collision.objectIndex2].isCollisionnable() == true) {
            scene->objects[collision.objectIndex2].setSpeed(glm::reflect(scene->objects[collision.objectIndex2].getSpeed(), collision.surfaceNormal1));
            glm::vec3 translation = scene->objects[collision.objectIndex2].getSpeed() * seconds;
            scene->objects[collision.objectIndex2].move(translation);
        }
    }
}

bool CollisionProcessor::process(GameObject* object1, GameObject* object2, float seconds,
        glm::vec3* collisionPoint, glm::vec3* surfaceNormal1, glm::vec3* surfaceNormal2) {
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
                    bool collision = checkForIntersection(point11, point12, point13, point21, point22, point23,
                        &intersection, &normal1, &normal2);
                    if(collision) {
                        intersections.push_back(intersection);
                        surfaceNormals1.push_back(normal1);
                        surfaceNormals2.push_back(normal2);
                    }
                }
            }
        }
    }
    if(intersections.size() > 0) {
        *collisionPoint = this->averagePoints(&intersections);
        *surfaceNormal1 = this->averageNormals(&surfaceNormals1);
        *surfaceNormal2 = this->averageNormals(&surfaceNormals2);
        return true;
    }

    return false;
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