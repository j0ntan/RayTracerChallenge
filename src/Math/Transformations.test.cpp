#include <numbers>
#include <gtest/gtest.h>
#include <Math/Vector.hpp>
#include <Math/Transformations.hpp>

/*
Scenario: Multiplying by a translation matrix
    Given transform <- translation(5, -3, 2)
        And p <- point(-3, 4, 5)
    Then transform * p = point(2, 1, 7)
*/
TEST(Translation, translatePoint)
{
    auto transform = translation(5, -3, 2);
    auto p = Point(-3, 4, 5);

    ASSERT_EQ(transform * p, Point(2, 1, 7));
}

/*
Scenario: Multiplying by the inverse of a translation matrix
    Given transform <- translation(5, -3, 2)
        And inv <- inverse(transform)
        And p <- point(-3, 4, 5)
    Then inv * p = point(-8, 7, 3)
*/
TEST(Translation, translatePointByInverse)
{
    auto transform = translation(5, -3, 2);
    auto inv = inverse(transform);
    auto p = Point(-3, 4, 5);

    ASSERT_EQ(inv * p, Point(-8, 7, 3));
}

/*
Scenario: Translation does not affect vectors
    Given transform <- translation(5, -3, 2)
        And v <- vector(-3, 4, 5)
    Then transform * v = v
*/
TEST(Translation, doesNotAffectVectors)
{
    auto transform = translation(5, -3, 2);
    auto v = Vector(-3, 4, 5);

    ASSERT_EQ(transform * v, v);
}

/*
Scenario: A scaling matrix applied to a point
    Given transform <- scaling(2, 3, 4)
        And p <- point(-4, 6, 8)
    Then transform * p = point(-8, 18, 32)
*/
TEST(Scaling, scaleAPoint)
{
    auto transform = scaling(2, 3, 4);
    auto p = Point(-4, 6, 8);

    ASSERT_EQ(transform * p, Point(-8, 18, 32));
}

/*
Scenario: A scaling matrix applied to a vector
    Given transform <- scaling(2, 3, 4)
        And v <- vector(-4, 6, 8)
    Then transform * v = vector(-8, 18, 32)
*/
TEST(Scaling, scaleAVector)
{
    auto transform = scaling(2, 3, 4);
    auto v = Vector(-4, 6, 8);

    ASSERT_EQ(transform * v, Vector(-8, 18, 32));
}

/*
Scenario: Multiplying by the inverse of a scaling matrix
    Given transform <- scaling(2, 3, 4)
        And inv <- inverse(transform)
        And v <- vector(-4, 6, 8)
    Then inv * v = vector(-2, 2, 2)
*/
TEST(Scaling, scaleVectorUsingInverse)
{
    auto transform = scaling(2, 3, 4);
    auto inv = inverse(transform);
    auto v = Vector(-4, 6, 8);

    ASSERT_EQ(inv * v, Vector(-2, 2, 2));
}

/*
Scenario: Reflection is scaling by a negative value
    Given transform <- scaling(-1, 1, 1)
        And p <- point(2, 3, 4)
    Then transform * p = point(-2, 3, 4)
*/
TEST(Scaling, reflectByScalingNegativeValue)
{
    auto transform = scaling(-1, 1, 1);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(-2, 3, 4));
}

/*
Scenario: Rotating a point around the x axis
    Given p <- point(0, 1, 0)
        And half_quarter <- rotation_x(pi / 4)
        And full_quarter <- rotation_x(pi / 2)
    Then half_quarter * p = point(0, sqrt(2) / 2, sqrt(2) / 2)
        full_quarter * p = point(0, 0, 1)
*/
TEST(Rotation, rotatePointAroundXAxis)
{
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_x(std::numbers::pi / 4);
    auto full_quarter = rotation_x(std::numbers::pi / 2);

    ASSERT_EQ(half_quarter * p,
              Point(0, std::numbers::sqrt2 / 2, std::numbers::sqrt2 / 2));
    ASSERT_EQ(full_quarter * p, Point(0, 0, 1));
}

/*
Scenario: The inverse of an x-rotation rotates in the opposite direction
    Given p <- point(0, 1, 0)
        And half_quarter <- rotation_x(pi / 4)
        And inv <- inverse(half_quarter)
    Then inv * p = point(0, sqrt(2) / 2, -sqrt(2) / 2)
*/
TEST(Rotation, rotatePointInverselyAroundXAxis)
{
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_x(std::numbers::pi / 4);
    auto full_quarter = rotation_x(std::numbers::pi / 2);

    ASSERT_EQ(half_quarter * p,
              Point(0, std::numbers::sqrt2 / 2, std::numbers::sqrt2 / 2));
    ASSERT_EQ(full_quarter * p, Point(0, 0, 1));
}

/*
Scenario: Rotating a point around the y axis
    Given p <- point(0, 0, 1)
        And half_quarter <- rotation_y(pi / 4)
        And full_quarter <- rotation_y(pi / 2)
    Then half_quarter * p = point(sqrt(2) / 2, 0, sqrt(2) / 2)
        full_quarter * p = point(1, 0, 0)
*/
TEST(Rotation, rotatePointAroundYAxis)
{
    auto p = Point(0, 0, 1);
    auto half_quarter = rotation_y(std::numbers::pi / 4);
    auto full_quarter = rotation_y(std::numbers::pi / 2);

    ASSERT_EQ(half_quarter * p,
              Point(std::numbers::sqrt2 / 2, 0, std::numbers::sqrt2 / 2));
    ASSERT_EQ(full_quarter * p, Point(1, 0, 0));
}

/*
Scenario: Rotating a point around the z axis
    Given p <- point(0, 1, 0)
        And half_quarter <- rotation_z(pi / 4)
        And full_quarter <- rotation_y(pi / 2)
    Then half_quarter * p = point(-sqrt(2) / 2, sqrt(2) / 2, 0)
        full_quarter * p = point(-1, 0, 0)
*/
TEST(Rotation, rotatePointAroundZAxis)
{
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_z(std::numbers::pi / 4);
    auto full_quarter = rotation_z(std::numbers::pi / 2);

    ASSERT_EQ(half_quarter * p,
              Point(-std::numbers::sqrt2 / 2, std::numbers::sqrt2 / 2, 0));
    ASSERT_EQ(full_quarter * p, Point(-1, 0, 0));
}

/*
Scenario: A shearing transformation moves x in proportion to y
    Given transform <- shearing(1, 0, 0, 0, 0, 0)
        And p <- point(2, 3, 4)
    Then transform * p = point(5, 3, 4)
*/
TEST(Shearing, moveXinProportionToY)
{
    auto transform = shearing(1, 0, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(5, 3, 4));
}

/*
Scenario: A shearing transformation moves x in proportion to z
    Given transform <- shearing(0, 1, 0, 0, 0, 0)
        And p <- point(2, 3, 4)
    Then transform * p = point(6, 3, 4)
*/
TEST(Shearing, moveXinProportionToZ)
{
    auto transform = shearing(0, 1, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(6, 3, 4));
}

/*
Scenario: A shearing transformation moves y in proportion to x
    Given transform <- shearing(0, 0, 1, 0, 0, 0)
        And p <- point(2, 3, 4)
    Then transform * p = point(2, 5, 4)
*/
TEST(Shearing, moveYinProportionToX)
{
    auto transform = shearing(0, 0, 1, 0, 0, 0);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 5, 4));
}

/*
Scenario: A shearing transformation moves y in proportion to z
    Given transform <- shearing(0, 0, 0, 1, 0, 0)
        And p <- point(2, 3, 4)
    Then transform * p = point(2, 7, 4)
*/
TEST(Shearing, moveYinProportionToZ)
{
    auto transform = shearing(0, 0, 0, 1, 0, 0);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 7, 4));
}

/*
Scenario: A shearing transformation moves z in proportion to x
    Given transform <- shearing(0, 0, 0, 0, 1, 0)
        And p <- point(2, 3, 4)
    Then transform * p = point(2, 3, 6)
*/
TEST(Shearing, moveZinProportionToX)
{
    auto transform = shearing(0, 0, 0, 0, 1, 0);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 3, 6));
}

/*
Scenario: A shearing transformation moves z in proportion to y
    Given transform <- shearing(0, 0, 0, 0, 0, 1)
        And p <- point(2, 3, 4)
    Then transform * p = point(2, 3, 7)
*/
TEST(Shearing, moveZinProportionToY)
{
    auto transform = shearing(0, 0, 0, 0, 0, 1);
    auto p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 3, 7));
}

/*
Scenario: Individual transformations are applied in sequence
    Given p <- point(1, 0, 1)
        And A <- rotation_x(pi / 2)
        And B <- scaling(5, 5, 5)
        And C <- translation(10, 5, 7)
    # apply rotation first
    When p2 <- A * p
    Then p2 = point(1, -1, 0)
    # then apply scaling
    When p3 <- B * p2
    Then p3 = point(5, -5, 0)
    # then apply translation
    When p4 <- C * p3
    Then p4 = point(15, 0, 7)
*/
TEST(ChainingTransformations, applyInSequence)
{
    auto p = Point(1, 0, 1);
    auto A = rotation_x(std::numbers::pi / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);

    // apply rotation first
    auto p2 = A * p;
    ASSERT_EQ(p2, Point(1, -1, 0));

    // then apply scaling
    auto p3 = B * p2;
    ASSERT_EQ(p3, Point(5, -5, 0));

    // then apply translation
    auto p4 = C * p3;
    ASSERT_EQ(p4, Point(15, 0, 7));
}

/*
Scenario: Chained translations must be applied in reverse order
    Given p <- point(1, 0, 1)
        And A <- rotation_x(pi / 2)
        And B <- scaling(5, 5, 5)
        And C <- translation(10, 5, 7)
    When T <- C * B * A
    Then T * p = point(15, 0, 7)
*/
TEST(ChainingTransformations, applyInReverseOrder)
{
    auto p = Point(1, 0, 1);
    auto A = rotation_x(std::numbers::pi / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);

    auto T = C * B * A;
    ASSERT_EQ(T * p, Point(15, 0, 7));
}

/*
Scenario: The transformation matrix for the default orientation
    Given from <- point(0, 0, 0)
        And to <- point(0, 0, -1)
        And up <- vector(0, 1, 0)
    When t <- view_transform(from, to, up)
    Then t = identity_matrix
*/
TEST(view_transform, forDefaultOrientation)
{
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, -1);
    auto up = Vector(0, 1, 0);

    auto t = view_transform(from, to, up);
    ASSERT_EQ(t, IDENTITY);
}

/*
Scenario: A view transformation matrix looking in positive z direction
    Given from <- point(0, 0, 0)
        And to <- point(0, 0, 1)
        And up <- vector(0, 1, 0)
    When t <- view_transform(from, to, up)
    Then t = scaling(-1, 1, -1)
*/
TEST(view_transform, inPositiveZDirection)
{
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, 1);
    auto up = Vector(0, 1, 0);

    auto t = view_transform(from, to, up);
    ASSERT_EQ(t, scaling(-1, 1, -1));
}

/*
Scenario: The view transformation moves the world
    Given from <- point(0, 0, 8)
        And to <- point(0, 0, 0)
        And up <- vector(0, 1, 0)
    When t <- view_transform(from, to, up)
    Then t = translation(0, 0, -8)
*/
TEST(view_transform, movesTheWorld)
{
    auto from = Point(0, 0, 8);
    auto to = Point(0, 0, 0);
    auto up = Vector(0, 1, 0);

    auto t = view_transform(from, to, up);
    ASSERT_EQ(t, translation(0, 0, -8));
}

/*
Scenario: An arbitrary view transformation
    Given from <- point(1, 3, 2)
        And to <- point(4, -2, 8)
        And up <- vector(1, 1, 0)
    When t <- view_transform(from, to, up)
    Then t is the following 4x4 matrix:
        | -0.50709 |  0.50709 |  0.67612 | -2.36643 |
        |  0.76772 |  0.60609 |  0.12122 | -2.82843 |
        | -0.35857 |  0.59761 | -0.71714 |  0.00000 |
        |  0.00000 |  0.00000 |  0.00000 |  1.00000 |
*/
TEST(view_transform, arbitraryViewTransformation)
{
    auto from = Point(1, 3, 2);
    auto to = Point(4, -2, 8);
    auto up = Vector(1, 1, 0);

    auto t = view_transform(from, to, up);
    ASSERT_EQ(t, Matrix<4>({-0.50709, 0.50709, 0.67612, -2.36643,
                            0.76772, 0.60609, 0.12122, -2.82843,
                            -0.35857, 0.59761, -0.71714, 0.00000,
                            0.00000, 0.00000, 0.00000, 1.00000}));
}
