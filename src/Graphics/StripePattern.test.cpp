#include <StripePattern.hpp>
#include <gtest/gtest.h>

/*
Background:
    Given black = color(0, 0, 0)
        And white = color(1, 1, 1)
*/
TEST(ColorConstants, defineBlackAndWhite)
{
    ASSERT_EQ(Color::BLACK, Color(0, 0, 0));
    ASSERT_EQ(Color::WHITE, Color(1, 1, 1));
}

/*
Scenario: Creating a stripe pattern
    Given pattern = stripe_pattern(white, black)
    Then pattern.a = white
        And pattern.b = black
*/
TEST(StripePatternCreate, matchProperties)
{
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.a, Color::WHITE);
    ASSERT_EQ(pattern.b, Color::BLACK);
}

/*
Scenario: A stripe pattern is constant in y
    Given pattern = stripe_pattern(white, black)
    Then stripe_at(pattern, point(0, 0, 0)) = white
        And stripe_at(pattern, point(0, 1, 0)) = white
        And stripe_at(pattern, point(0, 2, 0)) = white
*/
TEST(StripeAt, constantInY)
{
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.stripe_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(0, 1, 0)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(0, 2, 0)), Color::WHITE);
}

/*
Scenario: A stripe pattern is constant in z
    Given pattern = stripe_pattern(white, black)
    Then stripe_at(pattern, point(0, 0, 0)) = white
        And stripe_at(pattern, point(0, 0, 1)) = white
        And stripe_at(pattern, point(0, 0, 2)) = white
*/
TEST(StripeAt, constantInZ)
{
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.stripe_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(0, 0, 1)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(0, 0, 2)), Color::WHITE);
}

/*
Scenario: A stripe pattern alternates in x
    Given pattern = stripe_pattern(white, black)
    Then stripe_at(pattern, point(0, 0, 0)) = white
        And stripe_at(pattern, point(0.9, 0, 0)) = white
        And stripe_at(pattern, point(1, 0, 0)) = black
        And stripe_at(pattern, point(-0.1, 0, 0)) = black
        And stripe_at(pattern, point(-1, 0, 0)) = black
        And stripe_at(pattern, point(-1.1, 0, 0)) = white
*/
TEST(StripeAt, alternatesInX)
{
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);

    ASSERT_EQ(pattern.stripe_at(Point(0, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(0.9, 0, 0)), Color::WHITE);
    ASSERT_EQ(pattern.stripe_at(Point(1, 0, 0)), Color::BLACK);
    ASSERT_EQ(pattern.stripe_at(Point(-0.1, 0, 0)), Color::BLACK);
    ASSERT_EQ(pattern.stripe_at(Point(-1, 0, 0)), Color::BLACK);
    ASSERT_EQ(pattern.stripe_at(Point(-1.1, 0, 0)), Color::WHITE);
}
