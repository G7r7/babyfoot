#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(SolveEquations, EasyEquations) {
    float x1, y1, c1, x2, y2, c2, x, y;

    x1 = 2; y1 = 3; c1 = 12; x2 = 3; y2 = -4; c2 = 1; 
    solveEquations(x1, y1, c1, x2, y2, c2, &x, &y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 2);
}