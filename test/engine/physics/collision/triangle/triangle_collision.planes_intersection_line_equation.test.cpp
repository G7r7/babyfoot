#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>


TEST(TriangleCollisionPlaneIntersectionLineEquation, Intersection1) {
    {
        glm::vec3 normal_1 = {1, 2, 3};
        float d_1 = 4;
        glm::vec3 normal_2 = {4, 3, 2};
        float d_2 = 1;
        glm::vec3 direction;
        glm::vec3 point;
        planeIntersectionLineEquation(&normal_1, &d_1, &normal_2, &d_2, &direction, &point);
        // direction
        ASSERT_EQ(direction.x, -5);
        ASSERT_EQ(direction.y, 10);
        ASSERT_EQ(direction.z, -5);
        // point
        ASSERT_EQ(point.x, 2);
        ASSERT_EQ(point.y, -3);
        ASSERT_EQ(point.z, 0);
    }
}

TEST(TriangleCollisionPlaneIntersectionLineEquation, Intersection2) {
    {
        glm::vec3 normal_1 = {1, 0, 0};
        float d_1 = 0;
        glm::vec3 normal_2 = {0, 1, 0};
        float d_2 = 0;
        glm::vec3 direction;
        glm::vec3 point;
        planeIntersectionLineEquation(&normal_1, &d_1, &normal_2, &d_2, &direction, &point);
        // direction
        ASSERT_EQ(direction.x, 0);
        ASSERT_EQ(direction.y, 0);
        ASSERT_EQ(direction.z, 1);
        // point
        ASSERT_EQ(point.x, 0);
        ASSERT_EQ(point.y, 0);
        ASSERT_EQ(point.z, 0);
    }
}

TEST(TriangleCollisionPlaneIntersectionLineEquation, Intersection3) {
    {
        glm::vec3 normal_2 = {0, 1, 0};
        float d_1 = 0;
        glm::vec3 normal_1 = {0, 0, 1};
        float d_2 = 0;
        glm::vec3 direction;
        glm::vec3 point;
        planeIntersectionLineEquation(&normal_1, &d_1, &normal_2, &d_2, &direction, &point);
        // direction
        ASSERT_EQ(direction.x, -1);
        ASSERT_EQ(direction.y, 0);
        ASSERT_EQ(direction.z, 0);
        // point
        ASSERT_EQ(point.x, 0);
        ASSERT_EQ(point.y, 0);
        ASSERT_EQ(point.z, 0);
    }
}