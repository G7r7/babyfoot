#include "triangle_collision.hpp"
#include <iostream>
#include <algorithm>

void planeEquation(glm::vec3* v1, glm::vec3* v2, glm::vec3* v3, glm::vec3* normal, float* d) {
  glm::vec3 ab = *v2 - *v1;
  glm::vec3 ac = *v3 - *v1;
  *normal = glm::cross(ab, ac);
  *d = -(normal->x * v1->x + normal->y * v1->y + normal->z * v1->z);
};

float signedDistanceFromPlane(glm::vec3* v, glm::vec3* normal, float* d) {
  return (normal->x*v->x + normal->y*v->y + normal->z*v->z + *d) 
    / glm::sqrt(glm::pow(normal->x, 2) + glm::pow(normal->y, 2) + glm::pow(normal->z, 2)); 
};

bool sameSign(float d1, float d2, float d3) {
    if (d1 > 0 && d2 < 0)
        return false;
    if (d1 < 0 && d2 > 0)
        return false;
    if (d1 > 0 && d3 < 0)
        return false;
    if (d1 < 0 && d3 > 0)
        return false;
    if (d2 > 0 && d3 < 0)
        return false;
    if (d2 < 0 && d3 > 0)
        return false;
    return true;
}

bool solveEquations(float x1, float y1, float c1, float x2, float y2, float c2, float* x, float* y) {
    float determinant = x1*y2 - x2*y1;
    if(determinant == 0) { // There are either no solutions or many solutions exist.
      return false;
    }
    // Cramer equations system: result
    *x = (c1*y2 - y1*c2)/determinant;
    *y = (x1*c2 - c1*x2)/determinant;

    return true;
}

bool checkForIntervalOverlap(float* interval_1, float* interval_2) {
  int n1 = sizeof(interval_1) / sizeof(interval_1[0]);
  int n2 = sizeof(interval_2) / sizeof(interval_2[0]);
  std::sort(interval_1, interval_1 + n1);
  std::sort(interval_2, interval_2 + n2);
  return interval_1[0] <= interval_2[1] && interval_2[0] <= interval_1[1];
}

glm::vec3 planeIntersectionDirection(glm::vec3* normal_1, glm::vec3* normal_2) {
  return glm::cross(*normal_1, *normal_2);
}

void planeIntersectionLineEquation(glm::vec3* normal_1, float *d_1, glm::vec3* normal_2, float* d_2, glm::vec3* direction, glm::vec3* point) {
  *direction = planeIntersectionDirection(normal_1, normal_2);
  float x, y;
  bool success = false;
  // Trying with z = 0
  success = solveEquations(normal_1->x, normal_1->y, *d_1, normal_2->x, normal_2->y, *d_2, &x, &y);
  if (success) {
    *point = {x, y, 0};
    return;
  }
  // Trying with y = 0
  success = solveEquations(normal_1->x, normal_1->z, *d_1, normal_2->x, normal_2->z, *d_2, &x, &y);
  if (success) {
    *point = {x, 0, y};
    return;
  }
  // Trying with x = 0
  success = solveEquations(normal_1->y, normal_1->z, *d_1, normal_2->y, normal_2->z, *d_2, &x, &y);
  if (success) {
    *point = {0, x, y};
    return;
  }
}

bool checkForIntersection(glm::vec3 t0_v0, glm::vec3 t0_v1, glm::vec3 t0_v2,
  glm::vec3 t1_v0, glm::vec3 t1_v1, glm::vec3 t1_v2) {
  
  // Triangle 0 plane equation
  glm::vec3 t0_normal;
  float t0_d;
  planeEquation(&t0_v0, &t0_v1, &t0_v2, &t0_normal, &t0_d);

  // Triangle 1 plane equation
  glm::vec3 t1_normal;
  float t1_d;
  planeEquation(&t1_v0, &t1_v1, &t1_v2, &t1_normal, &t1_d);

  // Signed distances from triangle 0 vertices to plane of triangle 1
  float t0_v0_plane1 = signedDistanceFromPlane(&t0_v0, &t1_normal, &t1_d);
  float t0_v1_plane1 = signedDistanceFromPlane(&t0_v1, &t1_normal, &t1_d);
  float t0_v2_plane1 = signedDistanceFromPlane(&t0_v2, &t1_normal, &t1_d);

  // Signed distances from triangle 1 vertices to plane of triangle 0
  float t1_v0_plane0 = signedDistanceFromPlane(&t1_v0, &t0_normal, &t0_d);
  float t1_v1_plane0 = signedDistanceFromPlane(&t1_v1, &t0_normal, &t0_d);
  float t1_v2_plane0 = signedDistanceFromPlane(&t1_v2, &t0_normal, &t0_d);

  // If all distances are not 0 and all of same sign => no intersection
  if (t0_v0_plane1 != 0 && t0_v1_plane1 != 0 && t0_v2_plane1 != 0
    && sameSign(t0_v0_plane1, t0_v1_plane1, t0_v2_plane1)) { // For triangle 0 with plane 1
    if (t1_v0_plane0 != 0 && t1_v1_plane0 != 0 && t1_v2_plane0 != 0
      && sameSign(t1_v0_plane0, t1_v1_plane0, t1_v2_plane0)) { // For triangle 1 with plane 0
      return false; 
    }
  }

  // If all distances are 0 => Coplanar triangles
  if (t0_v0_plane1 == 0 && t0_v1_plane1 == 0 && t0_v2_plane1 == 0) {
    // TO DO
  }

  // Equation of the line of intersection between the 2 planes
  glm::vec3 D;
  glm::vec3 point_on_line;
  planeIntersectionLineEquation(&t0_normal, &t0_d, &t1_normal, &t1_d, &D, &point_on_line);

  // Scalar Projections of the triangle vertices on the line
  float proj_t0_v0 = glm::dot(D, (t0_v0 - point_on_line));
  float proj_t0_v1 = glm::dot(D, (t0_v1 - point_on_line));
  float proj_t0_v2 = glm::dot(D, (t0_v2 - point_on_line));

  // Then we want to compute a line parameter value corresponding with the intersection of the triangle and the line
  float t0_line_param_0 = proj_t0_v0 + (proj_t0_v1 - proj_t0_v0) * t0_v0_plane1 / (t0_v0_plane1 - t0_v1_plane1);
  float t0_line_param_1 = proj_t0_v2 + (proj_t0_v1 - proj_t0_v2) * t0_v2_plane1 / (t0_v2_plane1 - t0_v1_plane1);

  // Intersections points between triangle edges and the line 
  // glm::vec3 t0_B0 = point_on_line + t0_line_param_0 * D;
  // glm::vec3 t0_B1 = point_on_line + t0_line_param_1 * D;

  // Same thing for other triangle
  float proj_t1_v0 = glm::dot(D, (t1_v0 - point_on_line));
  float proj_t1_v1 = glm::dot(D, (t1_v1 - point_on_line));
  float proj_t1_v2 = glm::dot(D, (t1_v2 - point_on_line));
  float t1_line_param_0 = proj_t1_v0 + (proj_t1_v1 - proj_t1_v0) * t1_v0_plane0 / (t1_v0_plane0 - t1_v1_plane0);
  float t1_line_param_1 = proj_t1_v2 + (proj_t1_v1 - proj_t1_v2) * t1_v2_plane0 / (t1_v2_plane0 - t1_v1_plane0);
  // glm::vec3 t1_B0 = point_on_line + t1_line_param_0 * D;
  // glm::vec3 t1_B1 = point_on_line + t1_line_param_1 * D;

  float interval_0[2] = {t0_line_param_0, t0_line_param_1};
  float interval_1[2] = {t1_line_param_0, t1_line_param_1};

  std::cout << "Interval 0 : [" << interval_0[0] << "," << interval_0[1] << "]" << std::endl;
  std::cout << "Interval 1 : [" << interval_1[0] << "," << interval_1[1] << "]" << std::endl;
  
  // check for overlap in the intervals
  bool overlap = checkForIntervalOverlap(interval_0, interval_1);

  if (overlap) {
    return true;
  }

  return false;
};