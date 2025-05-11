#include <Math/Point.hpp>
#include <gtest/gtest.h>

/*
Scenario: point() creates tuples with w=1
    Given p <- point(4, -4, 3)
    Then p = tuple(4, -4, 3, 1)
*/
TEST(PointEqualsTuple, confirmEquality)
{
    auto p = Point{4, -4, 3};

    ASSERT_EQ(p, Point(Tuple(4, -4, 3, 1)));
}
