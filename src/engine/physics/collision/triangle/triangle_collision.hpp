#ifndef TRIANGLE_COLL_H
#define TRIANGLE_COLL_H

#include <glm/glm.hpp>

// A Fast Triangle-Triangle Intersection Test
// Tomas M ̈oller
// https://cis.temple.edu/~lakaemper/courses/cis350_2004/etc/moeller_triangle.pdf

void planeEquation(glm::vec3* v1, glm::vec3* v2, glm::vec3* v3, glm::vec3* normal, float* d);

float signedDistanceFromPlane(glm::vec3* v, glm::vec3* normal, float* d);

bool sameSign(float d1, float d2, float d3);

bool checkForIntersection(glm::vec3 v01, glm::vec3 v02, glm::vec3 v03, glm::vec3 v11, glm::vec3 v12, glm::vec3 v13);

bool solveEquations(float a1, float b1, float c1, float a2, float b2, float c2, float* x, float* y);

void planeIntersectionLineEquation(glm::vec3* normal_1, float* d_1, glm::vec3* normal_2, float* d_2, glm::vec3* direction, glm::vec3* point);

float sclalarProjectionPointOnLine(glm::vec3* point_to_project, glm::vec3* line_direction, glm::vec3* point_of_line);

bool checkForIntervalOverlap(float* interval_1, float* interval_2);

#endif