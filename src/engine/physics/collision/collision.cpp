#include "collision.hpp"

Collision Collision::getTransformed(glm::mat4 transformationMatrix) const {
    glm::vec3 newPoint = transformationMatrix * glm::vec4(point, 1.0);
    glm::vec3 newNormal1 = transformationMatrix * glm::vec4(surfaceNormal1, 1.0);
    glm::vec3 newNormal2 = transformationMatrix * glm::vec4(surfaceNormal2, 1.0);
    return {
        objectIndex1,
        objectIndex2,
        newPoint,
        newNormal1,
        newNormal2
    };
}