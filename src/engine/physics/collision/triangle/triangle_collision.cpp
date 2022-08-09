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

bool sameSign(float d1, float d2, float d3) 
{
    return d1 <= 0.f
        ? d2 <= 0.f && d3 <= 0.f
        : d2 > 0.f && d3 > 0.f;
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

bool checkForIntervalOverlap(float* interval_1, float* interval_2, float* interval_overlap) {
  bool overlap = interval_1[0] <= interval_2[1] && interval_2[0] <= interval_1[1];
  if(overlap) {
    if(interval_1[0] < interval_2[0])
      interval_overlap[0] = interval_2[0];
    else
      interval_overlap[0] = interval_1[0];
    if(interval_1[1] < interval_2[1])
      interval_overlap[1] = interval_1[1];
    else
      interval_overlap[1] = interval_2[1];
  }
  return overlap;
}

glm::vec3 planeIntersectionDirection(glm::vec3* normal_1, glm::vec3* normal_2) {
  return glm::normalize(glm::cross(*normal_1, *normal_2));
}

void planeIntersectionLineEquation(glm::vec3* normal_1, float *d_1, glm::vec3* normal_2, float* d_2, glm::vec3* direction, glm::vec3* point) {
  *direction = planeIntersectionDirection(normal_1, normal_2);
  float x, y;
  bool success = false;
  // Trying with z = 0
  success = solveEquations(normal_1->x, normal_1->y, -*d_1, normal_2->x, normal_2->y, -*d_2, &x, &y);
  if (success) {
    *point = {x, y, 0};
    return;
  }
  // Trying with y = 0
  success = solveEquations(normal_1->x, normal_1->z, -*d_1, normal_2->x, normal_2->z, -*d_2, &x, &y);
  if (success) {
    *point = {x, 0, y};
    return;
  }
  // Trying with x = 0
  success = solveEquations(normal_1->y, normal_1->z, -*d_1, normal_2->y, normal_2->z, -*d_2, &x, &y);
  if (success) {
    *point = {0, x, y};
    return;
  }
}

glm::vec3  projectionPointOnLine(glm::vec3* point_to_project, glm::vec3* line_direction, glm::vec3* point_of_line) {
  return *point_of_line
    + glm::dot(*point_to_project - *point_of_line, *line_direction)
    / glm::dot(*line_direction, *line_direction)
    * (*line_direction);
}


void scalarInterval(std::vector<glm::vec3>* vertices, float* signed_distances, glm::vec3* line_direction, glm::vec3* point_on_line, float* interval) {
  
  // Scalar Projections of the triangle vertices on the line
  float scalar_projections[3];
  scalar_projections[0] = glm::dot(*line_direction, (vertices->at(0) - *point_on_line));
  scalar_projections[1] = glm::dot(*line_direction, (vertices->at(1) - *point_on_line));
  scalar_projections[2] = glm::dot(*line_direction, (vertices->at(2) - *point_on_line));
  
  // Identify vertex that is on the other side than the 2 others
  int alone_index;
  if ((signed_distances[0] >= 0 && signed_distances[1] >= 0)
    || (signed_distances[0] < 0 && signed_distances[1] < 0)) {
    alone_index = 2;
  } else if ((signed_distances[1] >= 0 && signed_distances[2] >= 0)
    || (signed_distances[1] < 0 && signed_distances[2] < 0)) {
    alone_index = 0;
  } else {
    alone_index = 1;
  }
  int first_index = (alone_index + 2) % 3;
  int second_index = (alone_index + 1) % 3;

  // Then we want to compute a line parameter value corresponding with the intersection of the triangle and the line
  float line_param_0 = scalar_projections[first_index]
    + (scalar_projections[alone_index]
    - scalar_projections[first_index]) 
      * signed_distances[first_index]
      / (signed_distances[first_index]
    - signed_distances[alone_index]);
  float line_param_1 = scalar_projections[second_index]
    + (scalar_projections[alone_index]
    - scalar_projections[second_index])
      * signed_distances[second_index]
      / (signed_distances[second_index]
    - signed_distances[alone_index]);

  interval[0] = line_param_0;
  interval[1] = line_param_1;

  // Sorting the interval
  int n = sizeof(interval) / sizeof(interval[0]);
  std::sort(interval, interval + n);
}

bool checkForIntersection(glm::vec3 t0_v0, glm::vec3 t0_v1, glm::vec3 t0_v2,
  glm::vec3 t1_v0, glm::vec3 t1_v1, glm::vec3 t1_v2,
  glm::vec3* intersection, glm::vec3* surface_normal_0, glm::vec3* surface_normal_1) {

  std::vector<glm::vec3> t0_vertices = {t0_v0, t0_v1, t0_v2};
  std::vector<glm::vec3> t1_vertices = {t1_v0, t1_v1, t1_v2};

  // Triangle 0 plane equation
  glm::vec3 t0_normal;
  float t0_d;
  planeEquation(&t0_v0, &t0_v1, &t0_v2, &t0_normal, &t0_d);

  // Triangle 1 plane equation
  glm::vec3 t1_normal;
  float t1_d;
  planeEquation(&t1_v0, &t1_v1, &t1_v2, &t1_normal, &t1_d);

  // Signed distances from triangle 0 vertices to plane of triangle 1
  float t0_signed_distances[3] = {
    signedDistanceFromPlane(&t0_v0, &t1_normal, &t1_d),
    signedDistanceFromPlane(&t0_v1, &t1_normal, &t1_d),
    signedDistanceFromPlane(&t0_v2, &t1_normal, &t1_d)
  };

  // Signed distances from triangle 1 vertices to plane of triangle 0
  float t1_signed_distances[3] = {
    signedDistanceFromPlane(&t1_v0, &t0_normal, &t0_d),
    signedDistanceFromPlane(&t1_v1, &t0_normal, &t0_d),
    signedDistanceFromPlane(&t1_v2, &t0_normal, &t0_d)
  };

  // To prevent almost coplanar overlook, we set distance = 0 for distances below epsilon
  float epsilon = 0.000001;
  for (size_t i = 0; i < 3; i++)
  {
    if(glm::abs(t0_signed_distances[i]) < epsilon)
      t0_signed_distances[i] = 0;
  }
  for (size_t i = 0; i < 3; i++)
  {
    if(glm::abs(t1_signed_distances[i]) < epsilon)
      t1_signed_distances[i] = 0;
  }
  

  // If all distances are not 0 and all of same sign => no intersection
  // For triangle 0 with plane 1
  if (t0_signed_distances[0] != 0 && t0_signed_distances[1] != 0 && t0_signed_distances[2] != 0
    && sameSign(t0_signed_distances[0], t0_signed_distances[1], t0_signed_distances[2])) {
    return false;
  }
   // For triangle 1 with plane 0
  if (t1_signed_distances[0] != 0 && t1_signed_distances[1] != 0 && t1_signed_distances[2] != 0
    && sameSign(t1_signed_distances[0], t1_signed_distances[1], t1_signed_distances[2])) {
    return false; 
  }

  // If all distances are 0 => Coplanar triangles
  if (t0_signed_distances[0] == 0 && t0_signed_distances[1] == 0 && t0_signed_distances[2] == 0) {
    // TO DO
    // 2D Problem
    // std::cout << "Coplanaire !!!!" << std::endl;
    return false;
  }

  // Equation of the line of intersection between the 2 planes
  glm::vec3 D;
  glm::vec3 point_on_line;
  planeIntersectionLineEquation(&t0_normal, &t0_d, &t1_normal, &t1_d, &D, &point_on_line);

  float interval_0[2], interval_1[2], interval_overlap[2];
  scalarInterval(&t0_vertices, t0_signed_distances, &D, &point_on_line, interval_0);
  scalarInterval(&t1_vertices, t1_signed_distances, &D, &point_on_line, interval_1);

  // check for overlap in the intervals
  bool overlap = checkForIntervalOverlap(interval_0, interval_1, interval_overlap);

  if (overlap) {
    float overlap_average = interval_overlap[0] 
      + (interval_overlap[1]-interval_overlap[0])/2;
    *intersection = point_on_line + overlap_average * D;
    *surface_normal_0 = t0_normal;
    *surface_normal_1 = t1_normal;
    return true;
  }

  return false;
};