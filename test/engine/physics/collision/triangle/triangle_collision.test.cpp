#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(CheckForIntersection, Test1) {
    { // Same triangle rotated 90° (forming a "pine tree")
        glm::vec3 a1(-0.5, 0, 0);
        glm::vec3 b1(0.5, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(0,0,0.5);
        glm::vec3 b2(0,0,-0.5);
        glm::vec3 c2(0,1,0);
        
        glm::vec3 point_of_intersection;
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2, &point_of_intersection);

        ASSERT_TRUE(intersection);
        ASSERT_EQ(point_of_intersection.x, 0);
        ASSERT_EQ(point_of_intersection.y, 0.5);
        ASSERT_EQ(point_of_intersection.z, 0);
    }
}

TEST(CheckForIntersection, Test2) {
    { // Triangle clearly spaced appart
        glm::vec3 a1(-0.5, 0, 0);
        glm::vec3 b1(0.5, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(100,100,200.5);
        glm::vec3 b2(100,103,100.5);
        glm::vec3 c2(100,102,50);

        glm::vec3 point_of_intersection;
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2, &point_of_intersection);

        ASSERT_FALSE(intersection);
    }
}

TEST(CheckForIntersection, Test3) {
    { // Triangle crossing
        glm::vec3 a1(0, 0, 0);
        glm::vec3 b1(1, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(1,0,1);
        glm::vec3 b2(-1,0,1);
        glm::vec3 c2(0,1,-1);
        
        glm::vec3 point_of_intersection;
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2, &point_of_intersection);

        ASSERT_TRUE(intersection);
        ASSERT_EQ(point_of_intersection.x, 0.25);
        ASSERT_EQ(point_of_intersection.y, 0.5);
        ASSERT_EQ(point_of_intersection.z, 0);
    }
}
