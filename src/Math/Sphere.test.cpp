#include <Math/Sphere.hpp>
#include <Math/Ray.hpp>
#include <Math/Transformations.hpp>
#include <Interactions.hpp>
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
