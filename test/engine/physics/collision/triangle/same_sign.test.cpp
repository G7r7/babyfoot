#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(SameSign, AllZeros) {
    ASSERT_TRUE(sameSign(0, 0, 0));
}

TEST(SameSign, AllOnes) {
    ASSERT_TRUE(sameSign(1, 1, 1));
}

TEST(SameSign, AllSamesFloat) {
    ASSERT_TRUE(sameSign(2.5, 2.5, 2.5));
}

TEST(SameSign, AllNegativeDifferentFloats) {
    ASSERT_TRUE(sameSign(-0.12, -0.5, -0.6));
}

TEST(SameSign, LastNeg) {
    ASSERT_FALSE(sameSign(1, 1, -1));
}

TEST(SameSign, MiddleNeg) {
    ASSERT_FALSE(sameSign(1, -1, 1));
}

TEST(SameSign, FirstNeg) {
    ASSERT_FALSE(sameSign(-1, 1, 1));
}