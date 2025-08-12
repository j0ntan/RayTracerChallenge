#include <Math/Plane.hpp>
#include <MaterialCmp.hpp>
#include <gtest/gtest.h>

bool operator==(const Plane &lhs, const Plane &rhs)
{
    return lhs.material == rhs.material && lhs.transform == rhs.transform;
}

/*
Scenario: The normal of a plane is constant everywhere
    Given p = plane()
    When n1 = local_normal_at(p, point(0, 0, 0))
        And n2 = local_normal_at(p, point(10, 0, -10))
        And n3 = local_normal_at(p, point(-5, 0, 150))
    Then n1 = vector(0, 1, 0)
        And n2 = vector(0, 1, 0)
        And n3 = vector(0, 1, 0)
*/
TEST(PlaneNormal, isConstantEverywhere)
{
    auto p = Plane();

    auto n1 = p.local_normal_at(Point(0, 0, 0));
    auto n2 = p.local_normal_at(Point(10, 0, -10));
    auto n3 = p.local_normal_at(Point(-5, 0, 150));

    ASSERT_EQ(n1, Vector(0, 1, 0));
    ASSERT_EQ(n2, Vector(0, 1, 0));
    ASSERT_EQ(n3, Vector(0, 1, 0));
}

/*
Scenario: Intersect with a ray parallel to the plane
    Given p = plane()
        And r = ray(point(0, 10, 0), vector(0, 0, 1))
    When xs = local_intersect(p, r)
    Then xs is empty
*/
TEST(PlaneIntersect, rayParallelToPlane)
{
    auto p = Plane();
    auto r = Ray(Point(0, 10, 0), Vector(0, 0, 1));

    auto xs = p.local_intersect(r);

    ASSERT_TRUE(xs.empty());
}

/*
Scenario: Intersect with a coplanar ray
    Given p = plane()
        And r = ray(point(0, 0, 0), vector(0, 0, 1))
    When xs = local_intersect(p, r)
    Then xs is empty
*/
TEST(PlaneIntersect, coplanarRay)
{
    auto p = Plane();
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));

    auto xs = p.local_intersect(r);

    ASSERT_TRUE(xs.empty());
}

/*
Scenario: A ray intersecting a plane from above
    Given p = plane()
        And r = ray(point(0, 1, 0), vector(0, -1, 0))
    When xs = local_intersect(p, r)
    Then xs.count = 1
        And xs[0].t = 1
        And xs[0].object = p
*/
TEST(PlaneIntersect, intersectPlaneFromAbove)
{
    auto p = Plane();
    auto r = Ray(Point(0, 1, 0), Vector(0, -1, 0));

    auto xs = p.local_intersect(r);

    ASSERT_EQ(xs.size(), 1);
    ASSERT_FLOAT_EQ(xs[0].t, 1);
    ASSERT_EQ(*dynamic_cast<const Plane *>(xs[0].object), p);
}

/*
Scenario: A ray intersecting a plane from below
    Given p = plane()
        And r = ray(point(0, -1, 0), vector(0, 1, 0))
    When xs = local_intersect(p, r)
    Then xs.count = 1
        And xs[0].t = 1
        And xs[0].object = p
*/
TEST(PlaneIntersect, intersectPlaneFromBelow)
{
    auto p = Plane();
    auto r = Ray(Point(0, -1, 0), Vector(0, 1, 0));

    auto xs = p.local_intersect(r);

    ASSERT_EQ(xs.size(), 1);
    ASSERT_FLOAT_EQ(xs[0].t, 1);
    ASSERT_EQ(*dynamic_cast<const Plane *>(xs[0].object), p);
}
