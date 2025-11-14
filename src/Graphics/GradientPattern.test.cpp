#include <Graphics/GradientPattern.hpp>
#include <gtest/gtest.h>

/*
Scenario: A gradient linearly interpolates between colors
    Given pattern = gradient_pattern(white, black)
    Then pattern_at(pattern, point(0, 0, 0)) = white
        And pattern_at(pattern, point(0.25, 0, 0)) = color(0.75, 0.75, 0.75)
        And pattern_at(pattern, point(0.5, 0, 0)) = color(0.5, 0.5, 0.5)
        And pattern_at(pattern, point(0.75, 0, 0)) = color(0.25, 0.25, 0.25)
*/
TEST(GradientPatternInterpolate, matchGradientColors)
{
    auto pattern = GradientPattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
    ASSERT_EQ(pattern.pattern_at(Point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern.pattern_at(Point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}
