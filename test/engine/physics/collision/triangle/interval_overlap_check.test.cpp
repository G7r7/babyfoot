#include "../../../../../src/engine/physics/collision/triangle/triangle_collision.hpp"
#include <gtest/gtest.h>

TEST(IntervalOverlap, checkForIntervalOverlap) {
    {
        float interval_1[] = {0, 1};
        float interval_2[] = {2, 3};
        float interval_overlap[2];
        ASSERT_FALSE(checkForIntervalOverlap(interval_1, interval_2, interval_overlap));
    }
    {
        float interval_1[] = {2, 3};
        float interval_2[] = {-1, 0};
        float interval_overlap[2];
        ASSERT_FALSE(checkForIntervalOverlap(interval_1, interval_2, interval_overlap));
    }
    {
        float interval_1[] = {0, 2};
        float interval_2[] = {1, 3};
        float interval_overlap[2];
        ASSERT_TRUE(checkForIntervalOverlap(interval_1, interval_2, interval_overlap));
        ASSERT_EQ(interval_overlap[0], 1);
        ASSERT_EQ(interval_overlap[1], 2);
    }
    {
        float interval_1[] = {1, 3};
        float interval_2[] = {2, 3};
        float interval_overlap[2];
        ASSERT_TRUE(checkForIntervalOverlap(interval_1, interval_2, interval_overlap));
        ASSERT_EQ(interval_overlap[0], 2);
        ASSERT_EQ(interval_overlap[1], 3);
    }
}