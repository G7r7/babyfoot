#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(TriangleCollisionSameSign, AllZeros) {
    ASSERT_TRUE(sameSign(0, 0, 0));
}

TEST(TriangleCollisionSameSign, AllOnes) {
    ASSERT_TRUE(sameSign(1, 1, 1));
}

TEST(TriangleCollisionSameSign, AllSamesFloat) {
    ASSERT_TRUE(sameSign(2.5, 2.5, 2.5));
}

TEST(TriangleCollisionSameSign, AllNegativeDifferentFloats) {
    ASSERT_TRUE(sameSign(-0.12, -0.5, -0.6));
}

TEST(TriangleCollisionSameSign, LastNeg) {
    ASSERT_FALSE(sameSign(1, 1, -1));
}

TEST(TriangleCollisionSameSign, MiddleNeg) {
    ASSERT_FALSE(sameSign(1, -1, 1));
}

TEST(TriangleCollisionSameSign, FirstNeg) {
    ASSERT_FALSE(sameSign(-1, 1, 1));
}