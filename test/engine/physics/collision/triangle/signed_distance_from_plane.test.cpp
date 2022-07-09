#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(SignedDistanceFromPlane, PositiveDistance) {
    { // Positive
        glm::vec3 v = {1, 2, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_NEAR(signedDistanceFromPlane(&v, &normal, &d), 4.8107023544236, 0.1);
    }
}

TEST(SignedDistanceFromPlane, ZeroDistance) {
    { // On plane = 0
        glm::vec3 v = {1, -7, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_EQ(signedDistanceFromPlane(&v, &normal, &d), 0);
    }
}

TEST(SignedDistanceFromPlane, NegativeDistance) {
    { // Negative
        glm::vec3 v = {1, -20, 3};
        glm::vec3 normal = {1, 2, 3};
        float d = 4;
        ASSERT_NEAR(signedDistanceFromPlane(&v, &normal, &d), -6.948792289723034, 0.1);
    }
}