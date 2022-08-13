#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

// Plane equation
TEST(PlaneEquation, IntegersPlane) {
    glm::vec3 a, b, c, normal;
    float d;

    a = {1, 2, -2};
    b = {3, -2, 1};
    c = {5, 1, -4};
    planeEquation(a, b, c, normal, d);
    ASSERT_EQ(normal.x, 11);
    ASSERT_EQ(normal.y, 16);
    ASSERT_EQ(normal.z, 14);
    ASSERT_EQ(d, -15);
}

TEST(PlaneEquation, FloatsPlane) {
    glm::vec3 a, b, c, normal;
    float d;

    a = {748.2, -2.23, 902};
    b = {83, -2, 0.237};
    c = {0, 1, -4};
    planeEquation(a, b, c, normal, d);
    ASSERT_NEAR(normal.x, 2704.31, 0.5);
    ASSERT_NEAR(normal.y, 72027.8766, 0.5);
    ASSERT_NEAR(normal.z, -1976.51, 0.5);
    ASSERT_NEAR(d, -79933.9166, 0.5);
}