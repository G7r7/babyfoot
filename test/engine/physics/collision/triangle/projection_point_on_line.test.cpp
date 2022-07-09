#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(ProjectionPointOnLine, Test1) {
    glm::vec3 point_to_project(1,1,1);
    glm::vec3 line_direction(1, 0, 0);
    glm::vec3 point_on_line(0, 0, 0);
    glm::vec3 projection = projectionPointOnLine(&point_to_project, &line_direction, &point_on_line);
    ASSERT_FLOAT_EQ(projection.x, 1);
    ASSERT_FLOAT_EQ(projection.y, 0);
    ASSERT_FLOAT_EQ(projection.z, 0);
}

TEST(ProjectionPointOnLine, Test2) {
    glm::vec3 point_to_project(1,0,0);
    glm::vec3 line_direction(1, 1, 1);
    glm::vec3 point_on_line(0, 0, 0);
    glm::vec3 projection = projectionPointOnLine(&point_to_project, &line_direction, &point_on_line);
    ASSERT_FLOAT_EQ(projection.x, 0.3333334);
    ASSERT_FLOAT_EQ(projection.y, 0.3333334);
    ASSERT_FLOAT_EQ(projection.z, 0.3333334);
}

TEST(ProjectionPointOnLine, Test3) {
    glm::vec3 point_to_project(1.5, 5, 2.5);
    glm::vec3 line_direction(1, 2, 1);
    glm::vec3 point_on_line(2, 3, 4);
    glm::vec3 projection = projectionPointOnLine(&point_to_project, &line_direction, &point_on_line);
    ASSERT_FLOAT_EQ(projection.x, 2.3333333);
    ASSERT_FLOAT_EQ(projection.y, 3.6666667);
    ASSERT_FLOAT_EQ(projection.z, 4.3333333);
}