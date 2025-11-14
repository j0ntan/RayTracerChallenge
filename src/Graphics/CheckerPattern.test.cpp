#include <Graphics/CheckerPattern.hpp>
#include <gtest/gtest.h>

/*
Scenario: Checkers should repeat in x
    Given pattern = checkers_pattern(white, black)
    Then pattern_at(pattern, point(0, 0, 0)) = white
        And pattern_at(pattern, point(0.99, 0, 0)) = white
        And pattern_at(pattern, point(1.01, 0, 0)) = black
*/
TEST(CheckerPatternRepeats, repeatInX)
{
    auto pattern = CheckerPattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0.99, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(1.01, 0, 0)), Color::BLACK);
}

/*
Scenario: Checkers should repeat in y
    Given pattern = checkers_pattern(white, black)
    Then pattern_at(pattern, point(0, 0, 0)) = white
        And pattern_at(pattern, point(0, 0.99, 0)) = white
        And pattern_at(pattern, point(0, 1.01, 0)) = black
*/
TEST(CheckerPatternRepeats, repeatInY)
{
    auto pattern = CheckerPattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0, 0.99, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0, 1.01, 0)), Color::BLACK);
}

/*
Scenario: Checkers should repeat in z
    Given pattern = checkers_pattern(white, black)
    Then pattern_at(pattern, point(0, 0, 0)) = white
        And pattern_at(pattern, point(0, 0, 0.99)) = white
        And pattern_at(pattern, point(0, 0, 1.01)) = black
*/
TEST(CheckerPatternRepeats, repeatInZ)
{
    auto pattern = CheckerPattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 0.99)), Color::WHITE);
    ASSERT_EQ(pattern.pattern_at(Point(0, 0, 1.01)), Color::BLACK);
}
