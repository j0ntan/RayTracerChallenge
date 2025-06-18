#include <cmath>
#include <numbers>
#include <MaterialCmp.hpp>
#include <Math/Transformations.hpp>
#include <Interactions.hpp>
#include <Math/Sphere.hpp>
#include <gtest/gtest.h>

/*
Scenario: A sphere's default transformation
    Given s <- sphere()
    Then s.transform = identity_matrix
*/
TEST(SphereTransformation, hasDefaultTransformation)
{
    auto s = Sphere();
    ASSERT_EQ(s.transform, IDENTITY);
}

/*
Scenario: Changing a sphere's transformation
    Given s <- sphere()
        And t <- translation(2, 3, 4)
    When set_transform(s, t)
    Then s.transform = t
*/
TEST(SphereTransformation, changeTransformMatrix)
{
    auto s = Sphere();
    auto t = translation(2, 3, 4);

    s.transform = t;
    ASSERT_EQ(s.transform, t);
}

/*
Scenario: Intersecting a scaled sphere with a ray
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And s <- sphere()
    When set_transform(s, scaling(2, 2, 2))
        And xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0].t = 3
        And xs[1].t = 7
*/
TEST(SphereScaled, intersectRayWithScaled)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = Sphere();

    s.transform = scaling(2, 2, 2);
    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, 3);
    ASSERT_FLOAT_EQ(xs[1].t, 7);
}

/*
Scenario: The normal on a sphere at a point on the x axis
    Given s <- sphere()
    When n <- normal_at(s, point(1, 0, 0))
    Then n = vector(1, 0, 0)
*/
TEST(SphereNormal, normalAlongXAxis)
{
    auto s = Sphere();

    auto n = s.normal_at(Point(1, 0, 0));
    ASSERT_EQ(n, Vector(1, 0, 0));
}

/*
Scenario: The normal on a sphere at a point on the y axis
    Given s <- sphere()
    When n <- normal_at(s, point(0, 1, 0))
    Then n = vector(0, 1, 0)
*/
TEST(SphereNormal, normalAlongYAxis)
{
    auto s = Sphere();

    auto n = s.normal_at(Point(0, 1, 0));
    ASSERT_EQ(n, Vector(0, 1, 0));
}

/*
Scenario: The normal on a sphere at a point on the z axis
    Given s <- sphere()
    When n <- normal_at(s, point(0, 0, 1))
    Then n = vector(0, 0, 1)
*/
TEST(SphereNormal, normalAlongZAxis)
{
    auto s = Sphere();

    auto n = s.normal_at(Point(0, 0, 1));
    ASSERT_EQ(n, Vector(0, 0, 1));
}

/*
Scenario: The normal on a sphere at a nonaxial point
    Given s <- sphere()
    When n <- normal_at(s, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))
    Then n = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)
*/
TEST(SphereNormal, normalNonAxialPoint)
{
    auto s = Sphere();

    auto n = s.normal_at(Point(std::sqrt(3) / 3, std::sqrt(3) / 3,
                               std::sqrt(3) / 3));
    ASSERT_EQ(n, Vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));
}

/*
Scenario: The normal is a normalized vector
    Given s <- sphere()
    When n <- normal_at(s, point(√3/3, √3/3, √3/3))
    Then n = normalize(n)
*/
TEST(SphereNormal, isNormalizedVector)
{
    auto s = Sphere();
    auto n = s.normal_at(Point(std::sqrt(3) / 3, std::sqrt(3) / 3,
                               std::sqrt(3) / 3));
    ASSERT_EQ(n, normalize(n));
}

/*
Scenario: Computing the normal on a translated sphere
    Given s <- sphere()
        And set_transform(s, translation(0, 1, 0))
    When n <- normal_at(s, point(0, 1.70711, -0.70711))
    Then n = vector(0, 0.70711, -0.70711)
*/
TEST(SphereNormal, accountForTranslation)
{
    auto s = Sphere();
    s.transform = translation(0, 1, 0);

    auto n = s.normal_at(Point(0, 1.70711, -0.70711));
    ASSERT_EQ(n, Vector(0, 0.70711, -0.70711));
}

/*
Scenario: Computing the normal on a transformed sphere
    Given s <- sphere()
        And m <- scaling(1, 0.5, 1) * rotation_z(π/5)
        And set_transform(s, m)
    When n <- normal_at(s, point(0, √2/2, -√2/2))
    Then n = vector(0, 0.97014, -0.24254)
 */
TEST(SphereNormal, accountForTransformation)
{
    auto s = Sphere();
    auto m = scaling(1, 0.5, 1) * rotation_z(std::numbers::pi / 5);
    s.transform = m;

    auto n = s.normal_at(
        Point(0, std::numbers::sqrt2 / 2, -std::numbers::sqrt2 / 2));
    ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));
}

/*
Scenario: A sphere has a default material
    Given s <- sphere()
    When m <- s.material
    Then m = material()
*/
TEST(SphereMaterial, hasDefaultMaterial)
{
    auto s = Sphere();

    auto m = s.material;
    ASSERT_EQ(m, Material{});
}

/*
Scenario: A sphere may be assigned a material
    Given s <- sphere()
        And m <- material()
        And m.ambient <- 1
    When s.material <- m
    Then s.material = m
*/
TEST(SphereMaterial, isAssignable)
{
    auto s = Sphere();
    auto m = Material();
    m.ambient = 1;

    s.material = m;
    ASSERT_EQ(s.material, m);
}
