#include <cmath>
#include <numbers>
#include <Math/Vector.hpp>
#include <gtest/gtest.h>

/*
Scenario: vector() creates tuples with w=0
    Given v <- vector(4, -4, 3)
    Then v = tuple(4, -4, 3, 0)
*/
TEST(VectorEqualsTuple, confirmEquality)
{
    auto v = Vector{4, -4, 3};

    ASSERT_EQ(v, Vector(Tuple(4, -4, 3, 0)));
}

/*
Scenario: Subtracting two points
    Given p1 <- point(3, 2, 1)
        And p2 <- point(5, 6, 7)
    Then p1 - p2 = vector(-2, -4, -6)
*/
TEST(VectorPointSubtractionOp, createVectorFromPoints)
{
    auto p1 = Point{3, 2, 1};
    auto p2 = Point{5, 6, 7};

    ASSERT_EQ(p1 - p2, Vector(-2, -4, -6));
}

/*
Scenario: Subtracting a vector from a point
    Given p <- point(3, 2, 1)
        and v <- vector(5, 6, 7)
    Then p - v = point(-2, -4, -6)
*/
TEST(VectorPointSubtractOp, movePointByVectorAmount)
{
    auto p = Point{3, 2, 1};
    auto v = Vector{5, 6, 7};

    ASSERT_EQ(p - v, Point(-2, -4, -6));
}

/*
Scenario: Subtracting two vectors
    Given v1 <- vector(3, 2, 1)
        and v2 <- vector(5, 6, 7)
    Then v1 - v2 = vector(-2, -4, -6)
*/
TEST(VectorSubtractVectorOp, getDifferenceOfVectors)
{
    auto v1 = Vector{3, 2, 1};
    auto v2 = Vector{5, 6, 7};

    ASSERT_EQ(v1 - v2, Vector(-2, -4, -6));
}

/*
Scenario: Subtracting a vector from the zero vector
    Given zero <- vector(0, 0, 0)
        And v <- vector(1, -2, 3)
    Then zero - v = vector(-1, 2, -3)
*/
TEST(VectorSubtractVectorOp, subtractFromZeroVector)
{
    auto zero = Vector{0, 0, 0};
    auto v = Vector{1, -2, 3};

    ASSERT_EQ(zero - v, Vector(-1, 2, -3));
}

/*
Scenario: Computing the magnitude of vector(1, 0, 0)
    Given v <- vector(1, 0, 0)
    Then magnitude(v) = 1

Scenario: Computing the magnitude of vector(0, 1, 0)
    Given v <- vector(0, 1, 0)
    Then magnitude(v) = 1

Scenario: Computing the magnitude of vector(0, 0, 1)
    Given v <- vector(0, 0, 1)
    Then magnitude(v) = 1

Scenario: Computing the magnitude of vector(1, 2, 3)
    Given v <- vector(1, 2, 3)
    Then magnitude(v) = sqrt(14)

Scenario: Computing the magnitude of vector(-1, -2, -3)
    Given v <- vector(1, 0, 0)
    Then magnitude(v) = sqrt(14)
*/
TEST(VectorMagnitude, calculateValues)
{
    auto v = Vector{1, 0, 0};
    ASSERT_FLOAT_EQ(magnitude(v), 1);

    v = Vector{0, 1, 0};
    ASSERT_FLOAT_EQ(magnitude(v), 1);

    v = Vector{0, 0, 1};
    ASSERT_FLOAT_EQ(magnitude(v), 1);

    v = Vector{1, 2, 3};
    ASSERT_FLOAT_EQ(magnitude(v), std::sqrt(14));

    v = Vector{-1, -2, -3};
    ASSERT_FLOAT_EQ(magnitude(v), std::sqrt(14));
}

/*
Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)
    Given v <- vector(4, 0, 0)
    Then normalize(v) = vector(1, 0, 0)
*/
TEST(VectorNormalize, normalizeSingleComponentVector)
{
    auto v = Vector{4, 0, 0};

    ASSERT_EQ(normalize(v), Vector(1, 0, 0));
}

/*
Scenario: Normalizing vector(1, 2, 3)
    Given v <- vector(1, 2, 3)
    Then normalize(v) = vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14))
*/
TEST(VectorNormalize, normalizeThreeComponentVector)
{
    auto v = Vector{1, 2, 3};

    ASSERT_EQ(normalize(v),
              Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
}

/*
Scenario: The magnitude of a normalized vector
    Given v <- vector(1, 2, 3)
    When norm <- normalize(v)
    Then magnitude(norm) = 1
*/
TEST(VectorNormalize, magnitudeIsUnity)
{
    auto v = Vector{1, 2, 3};

    auto norm = normalize(v);
    ASSERT_FLOAT_EQ(magnitude(norm), 1);
}

/*
Scenario: The dot product of two tuples
    Given a <- vector(1, 2, 3)
        And b <- vector(2, 3, 4)
    Then dot(a, b) = 20
*/
TEST(VectorDotProduct, calculateDotProduct)
{
    auto a = Vector{1, 2, 3};
    auto b = Vector{2, 3, 4};

    ASSERT_FLOAT_EQ(dot(a, b), 20);
}

/*
Scenario: The cross product of two vectors
    Given a <- vector(1, 2, 3)
        And b <- vector(2, 3, 4)
    Then cross(a, b) = vector(-1, 2, -1)
        And cross(b, a) = vector(1, -2, 1)
*/
TEST(VectorCrossProduct, calculateCrossProduct)
{
    auto a = Vector{1, 2, 3};
    auto b = Vector{2, 3, 4};

    ASSERT_EQ((cross(a, b)), (Vector{-1, 2, -1}));
    ASSERT_EQ((cross(b, a)), (Vector{1, -2, 1}));
}

/*
Scenario: Reflecting a vector approaching at 45°
    Given v <- vector(1, -1, 0)
        And n <- vector(0, 1, 0)
    When r <- reflect(v, n)
    Then r = vector(1, 1, 0)
*/
TEST(Reflect, reflectIncidentAt45Degrees)
{
    auto v = Vector(1, -1, 0);
    auto n = Vector(0, 1, 0);

    auto r = reflect(v, n);
    ASSERT_EQ(r, Vector(1, 1, 0));
}

/*
Scenario: Reflecting a vector off a slanted surface
    Given v <- vector(0, -1, 0)
        And n <- vector(sqrt(2) / 2, sqrt(2) / 2, 0)
    When r <- reflect(v, n)
    Then r = vector(1, 0, 0)
*/
TEST(Reflect, reflectOffSlantedSurface)
{
    auto v = Vector(0, -1, 0);
    auto n = Vector(std::numbers::sqrt2 / 2, std::numbers::sqrt2 / 2, 0);

    auto r = reflect(v, n);
    ASSERT_EQ(r, Vector(1, 0, 0));
}
