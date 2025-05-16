#include <Graphics/Color.hpp>
#include <gtest/gtest.h>

/*
Scenario: Colors are (red, green, blue) tuples
    Given c <- color(-0.5, 0.4, 1.7)
    Then c.red = -0.5
        And c.green = 0.4
        And c.blue = 1.7
*/
TEST(ColorComponents, matchInitialValues)
{
    auto c = Color{-0.5, 0.4, 1.7};

    ASSERT_FLOAT_EQ(c.red(), -0.5);
    ASSERT_FLOAT_EQ(c.green(), 0.4);
    ASSERT_FLOAT_EQ(c.blue(), 1.7);
}

/*
Scenario: Adding colors
    Given c1 <- color(0.9, 0.6, 0.75)
        And c2 <- color(0.7, 0.1, 0.25)
    Then c1 + c2 = color(1.6, 0.7, 1.0)
*/
TEST(ColorAdditionOp, matchAddedColors)
{
    auto c1 = Color{0.9, 0.6, 0.75};
    auto c2 = Color{0.7, 0.1, 0.25};

    ASSERT_EQ(c1 + c2, Color(1.6, 0.7, 1.0));
}

/*
Scenario: Subtracting colors
    Given c1 <- color(0.9, 0.6, 0.75)
        And c2 <- color(0.7, 0.1, 0.25)
    Then c1 + c2 = color(0.2, 0.5, 0.5)
*/
TEST(ColorSubtractionOp, matchSubtractedColors)
{
    auto c1 = Color{0.9, 0.6, 0.75};
    auto c2 = Color{0.7, 0.1, 0.25};

    ASSERT_EQ(c1 - c2, Color(0.2, 0.5, 0.5));
}

/*
Scenario: Multiplying a color by a scalar
    Given c <- color(0.2, 0.3, 0.4)
    Then c * 2 = color(0.4, 0.6, 0.8)
*/
TEST(ColorScalarOp, matchScaledColors)
{
    auto c = Color{0.2, 0.3, 0.4};

    ASSERT_EQ(c * 2, Color(0.4, 0.6, 0.8));
}

/*
Scenario: Multiplying colors
    Given c1 <- color(1, 0.2, 0.4)
        And c2 <- color(0.9, 1, 0.1)
    Then c1 * c2 = color(0.9, 0.2, 0.04)
*/
TEST(ColorMultiplicationOp, matchMultipliedColors)
{
    auto c1 = Color{1, 0.2, 0.4};
    auto c2 = Color{0.9, 1, 0.1};

    ASSERT_EQ(c1 * c2, Color(0.9, 0.2, 0.04));
}
