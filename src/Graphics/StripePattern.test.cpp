#include <Graphics/StripePattern.hpp>
#include <Math/Transformations.hpp>
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

/*
Scenario: Stripes with an object transformation
    Given object ← sphere()
        And set_transform(object, scaling(2, 2, 2))
        And pattern ← stripe_pattern(white, black)
    When c ← stripe_at_object(pattern, object, point(1.5, 0, 0))
    Then c = white
*/
TEST(StripePatternTransformation, hasObjectTransformation)
{
    auto object = Sphere();
    object.transform = scaling(2, 2, 2);
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);

    auto c = stripe_at_object(pattern, object, Point(1.5, 0, 0));

    ASSERT_EQ(c, Color::WHITE);
}

/*
Scenario: Stripes with a pattern transformation
    Given object ← sphere()
        And pattern ← stripe_pattern(white, black)
        And set_pattern_transform(pattern, scaling(2, 2, 2))
    When c ← stripe_at_object(pattern, object, point(1.5, 0, 0))
    Then c = white
*/
TEST(StripePatternTransformation, hasPatternTransformation)
{
    auto object = Sphere();
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);
    pattern.transform = scaling(2, 2, 2);

    auto c = stripe_at_object(pattern, object, Point(1.5, 0, 0));

    ASSERT_EQ(c, Color::WHITE);
}

/*
Scenario: Stripes with both an object and a pattern transformation
    Given object ← sphere()
        And set_transform(object, scaling(2, 2, 2))
        And pattern ← stripe_pattern(white, black)
        And set_pattern_transform(pattern, translation(0.5, 0, 0))
    When c ← stripe_at_object(pattern, object, point(2.5, 0, 0))
    Then c = white
*/
TEST(StripePatternTransformation, hasObjectAndPatternTransformation)
{
    auto object = Sphere();
    object.transform = scaling(2, 2, 2);
    auto pattern = StripePattern(Color::WHITE, Color::BLACK);
    pattern.transform = translation(0.5, 0, 0);

    auto c = stripe_at_object(pattern, object, Point(2.5, 0, 0));

    ASSERT_EQ(c, Color::WHITE);
}
