#ifndef COLL_H
#define COLL_H

#include <glm/glm.hpp>

struct Collision {
    int objectIndex1;
    int objectIndex2;
    glm::vec3 point;
    glm::vec3 surfaceNormal1;
    glm::vec3 surfaceNormal2;
    Collision getTransformed(glm::mat4 transformationMatrix) const;
};

#endif