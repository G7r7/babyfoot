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
        
        auto collision = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_TRUE(collision.has_value());
        ASSERT_EQ(collision->point.x, 0);
        ASSERT_EQ(collision->point.y, 0.5);
        ASSERT_EQ(collision->point.z, 0);
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
        glm::vec3 surface_normal_0;
        glm::vec3 surface_normal_1;
        auto collision = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_FALSE(collision.has_value());
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
        glm::vec3 surface_normal_0;
        glm::vec3 surface_normal_1;
        auto collision = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_TRUE(collision.has_value());
        ASSERT_EQ(collision->point.x, 0.25);
        ASSERT_EQ(collision->point.y, 0.5);
        ASSERT_EQ(collision->point.z, 0);
    }
}

TEST(CheckForIntersection, Test4)
{
    { // Triangles that should not be crossing
        glm::vec3 a1(0.127735287, 1.2434237, -0.0286270082);
        glm::vec3 b1(0.143611282, 1.25942874, -0.043016009);
        glm::vec3 c1(0.143611282, 1.23977673, -0.0323070064);

        glm::vec3 a2(0.323366135, 1.12013936, -0.0430160053);
        glm::vec3 b2(0.323366135, 1.13979137, -0.0323070027);
        glm::vec3 c2(0.339242131, 1.1361444, -0.0286270045);

        glm::vec3 point_of_intersection;
        glm::vec3 surface_normal_0;
        glm::vec3 surface_normal_1;
        auto collision = checkForIntersection(a1, b1, c1, a2, b2, c2);

        ASSERT_FALSE(collision.has_value());
    }
}
