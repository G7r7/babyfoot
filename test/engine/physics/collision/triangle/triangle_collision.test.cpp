#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(IntervalOverlap, checkForIntervalOverlap) {
    {
        float interval_1[] = {0, 1};
        float interval_2[] = {2, 3};
        ASSERT_FALSE(checkForIntervalOverlap(interval_1, interval_2));
    }
    {
        float interval_1[] = {2, 3};
        float interval_2[] = {-1, 0};
        ASSERT_FALSE(checkForIntervalOverlap(interval_1, interval_2));
    }
    {
        float interval_1[] = {0, 2};
        float interval_2[] = {1, 3};
        ASSERT_TRUE(checkForIntervalOverlap(interval_1, interval_2));
    }
    {
        float interval_1[] = {1, 3};
        float interval_2[] = {2, 3};
        ASSERT_TRUE(checkForIntervalOverlap(interval_1, interval_2));
    }
    { // flipped
        float interval_1[] = {3, 1};
        float interval_2[] = {2, 3};
        ASSERT_TRUE(checkForIntervalOverlap(interval_1, interval_2));
    }
}


TEST(CheckForIntersection, Test1) {
    { // Same triangle rotated 90° (forming a "pine tree")
        glm::vec3 a1(-0.5, 0, 0);
        glm::vec3 b1(0.5, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(0,0,0.5);
        glm::vec3 b2(0,0,-0.5);
        glm::vec3 c2(0,1,0);
        
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_TRUE(intersection);
    }
    { // Triangle clearly spaced appart
        glm::vec3 a1(-0.5, 0, 0);
        glm::vec3 b1(0.5, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(100,100,200.5);
        glm::vec3 b2(100,103,100.5);
        glm::vec3 c2(100,102,50);
        
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_FALSE(intersection);
    }
    { // Triangle crossing
        glm::vec3 a1(0, 0, 0);
        glm::vec3 b1(1, 0, 0);
        glm::vec3 c1(0, 1, 0);

        glm::vec3 a2(1,0,1);
        glm::vec3 b2(-1,0,1);
        glm::vec3 c2(0,1,-1);
        
        bool intersection = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_TRUE(intersection);
    }
}
