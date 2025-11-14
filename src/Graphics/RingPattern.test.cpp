#include <Graphics/RingPattern.hpp>
#include <gtest/gtest.h>

/*
Scenario: A ring should extend in both x and z
    Given pattern = ring_pattern(white, black)
    Then pattern_at(pattern, point(0, 0, 0)) = white
        And pattern_at(pattern, point(1, 0, 0)) = black
        And pattern_at(pattern, point(0, 0, 1)) = black
        # 0.708 = just slightly more than sqr(2)/2
        And pattern_at(pattern, point(0.708, 0, 0.708)) = black
*/
TEST(GradientPatternInterpolate, matchGradientColors)
{
    auto pattern = RingPattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(1, 0, 0)), Color::BLACK);
    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 1)), Color::BLACK);
    ASSERT_EQ(pattern.pattern_at(Point(0.708, 0, 0.708)), Color::BLACK);
}
