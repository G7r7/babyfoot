#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

// Same sign function
TEST(TriangleCollision, sameSign) {
    ASSERT_TRUE(sameSign(0, 0, 0));
    ASSERT_TRUE(sameSign(1, 1, 1));
    ASSERT_TRUE(sameSign(2.5, 2.5, 2.5));
    ASSERT_TRUE(sameSign(-0.12, -0.5, -0.6));
    ASSERT_FALSE(sameSign(1, 1, -1));
    ASSERT_FALSE(sameSign(1, -1, 1));
    ASSERT_FALSE(sameSign(-1, 1, 1));
}

// Plane equation
TEST(TriangleCollision, planeEquation) {
    glm::vec3 a, b, c, normal;
    float d;

    a = {1, 2, -2};
    b = {3, -2, 1};
    c = {5, 1, -4};
    planeEquation(&a, &b, &c, &normal, &d);
    ASSERT_EQ(normal.x, 11);
    ASSERT_EQ(normal.y, 16);
    ASSERT_EQ(normal.z, 14);
    ASSERT_EQ(d, -15);

    a = {748.2, -2.23, 902};
    b = {83, -2, 0.237};
    c = {0, 1, -4};
    planeEquation(&a, &b, &c, &normal, &d);
    ASSERT_NEAR(normal.x, 2704.31, 0.5);
    ASSERT_NEAR(normal.y, 72027.8766, 0.5);
    ASSERT_NEAR(normal.z, -1976.51, 0.5);
    ASSERT_NEAR(d, -79933.9166, 0.5);
}

TEST(TriangleCollision, signedDistanceFromPlane) {
    { // Positive
        glm::vec3 v = {1, 2, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_NEAR(signedDistanceFromPlane(&v, &normal, &d), 4.8107023544236, 0.1);
    }
    { // On plane = 0
        glm::vec3 v = {1, -7, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_EQ(signedDistanceFromPlane(&v, &normal, &d), 0);
    }
    { // Negative
        glm::vec3 v = {1, -20, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_NEAR(signedDistanceFromPlane(&v, &normal, &d), -6.948792289723034, 0.1);
    }
}

TEST(TriangleCollision, solveEquation) {
    float x1, y1, c1, x2, y2, c2, x, y;

    x1 = 2; y1 = 3; c1 = 12; x2 = 3; y2 = -4; c2 = 1; 
    solveEquations(x1, y1, c1, x2, y2, c2, &x, &y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 2);
}

TEST(TriangleOverlap, checkForIntervalOverlap) {
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

TEST(TriangleCollision, planeIntersectionLineEquation) {
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
        ASSERT_EQ(point.x, -2);
        ASSERT_EQ(point.y, 3);
        ASSERT_EQ(point.z, 0);
    }
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

TEST(TriangleCollision, checkForIntersection) {
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
}
