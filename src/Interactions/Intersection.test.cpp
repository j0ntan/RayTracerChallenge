#include <Interactions.hpp>
#include <Float_compare.hpp>
#include <Math/Transformations.hpp>
#include <gtest/gtest.h>

/*
Scenario: A ray intersects a sphere at two points
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0] = 4.0
        And xs[1] = 6.0
*/
TEST(IntersectSphere, intersectTwoPoints)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, 4.0);
    ASSERT_FLOAT_EQ(xs[1].t, 6.0);
}

/*
Scenario: A ray intersects a sphere at a tangent
    Given r <- ray(point(0, 1, -5), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0] = 5.0
        And xs[1] = 5.0
*/
TEST(IntersectSphere, intersectAtTangentPoint)
{
    auto r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, 5.0);
    ASSERT_FLOAT_EQ(xs[1].t, 5.0);
}

/*
Scenario: A ray misses a sphere
    Given r <- ray(point(0, 2, -5), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 0
*/
TEST(IntersectSphere, missesASphere)
{
    auto r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 0);
}

/*
Scenario: A ray originates inside a sphere
    Given r <- ray(point(0, 0, 0), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0] = -1.0
        And xs[1] = 1.0
 */
TEST(IntersectSphere, rayInsideSphereIntersects)
{
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, -1.0);
    ASSERT_FLOAT_EQ(xs[1].t, 1.0);
}

/*
Scenario: A sphere is behind a ray
    Given r <- ray(point(0, 0, 5), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0] = -6.0
        And xs[1] = -4.0
*/
TEST(IntersectSphere, sphereBehindRay)
{
    auto r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, -6.0);
    ASSERT_FLOAT_EQ(xs[1].t, -4.0);
}

/*
Scenario: An intersection encapsulates t and object
    Given s <- sphere()
    When i <- intersection(3.5, s)
    Then i.t = 3.5
        And i.object = s
*/
TEST(Intersection, matchInitialValues)
{
    auto s = Sphere();

    auto i = Intersection(3.5, &s);
    ASSERT_FLOAT_EQ(i.t, 3.5);
    ASSERT_EQ(i.object, &s);
}

/*
Scenario: Aggregating intersections
    Given s <- sphere()
        And i1 <- intersection(1, s)
        And i2 <- intersection(2, s)
    When xs <- intersections(i1, i2)
    Then xs.count = 2
        And xs[0].t = 1
        And xs[1].t = 2
*/
TEST(Intersections, aggregateIndividualIntersections)
{
    auto s = Sphere();
    auto i1 = Intersection(1, &s);
    auto i2 = Intersection(2, &s);

    auto xs = intersections({i1, i2});
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].t, 1);
    ASSERT_FLOAT_EQ(xs[1].t, 2);
}

/*
Scenario: Intersect sets the object on the intersection
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And s <- sphere()
    When xs <- intersect(s, r)
    Then xs.count = 2
        And xs[0].object = s
        And xs[1].object = s
*/
TEST(IntersectObject, setTheIntersectingObject)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = Sphere();

    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].object, &s);
    ASSERT_EQ(xs[1].object, &s);
}

bool operator==(const Intersection &lhs, const Intersection &rhs)
{
    return lhs.t == rhs.t && lhs.object == rhs.object;
}

/*
Scenario: The hit, when all intersections have positive t
    Given s <- sphere()
        And i1 <- intersection(1, s)
        And i2 <- intersection(2, s)
        And xs <- intersections(i2, i1)
    When i <- hit(xs)
    Then i = i1
*/
TEST(Hit, findLeastPositiveHit)
{
    auto s = Sphere();
    auto i1 = Intersection(1, &s);
    auto i2 = Intersection(2, &s);
    auto xs = intersections({i2, i1});

    auto i = hit(xs);
    ASSERT_EQ(*i, i1);
}

/*
Scenario: The hit, when some intersections have negative t
    Given s <- sphere()
        And i1 <- intersection(-1, s)
        And i2 <- intersection(1, s)
        And xs <- intersections(i2, i1)
    When i <- hit(xs)
    Then i = i2
*/
TEST(Hit, excludeNegativeHit)
{
    auto s = Sphere();
    auto i1 = Intersection(-1, &s);
    auto i2 = Intersection(1, &s);
    auto xs = intersections({i2, i1});

    auto i = hit(xs);
    ASSERT_EQ(i, i2);
}

/*
Scenario: The hit, when all intersections have negative t
    Given s <- sphere()
        And i1 <- intersection(-2, s)
        And i2 <- intersection(-1, s)
        And xs <- intersections(i2, i1)
    When i <- hit(xs)
    Then i is nothing
*/
TEST(Hit, noHitForAllNegativeIntersections)
{
    auto s = Sphere();
    auto i1 = Intersection(-2, &s);
    auto i2 = Intersection(-1, &s);
    auto xs = intersections({i2, i1});

    auto i = hit(xs);
    ASSERT_FALSE(i.has_value());
}

/*
Scenario: The hit is always the lowest nonnegative intersection
    Given s <- sphere()
        And i1 <- intersection(5, s)
        And i2 <- intersection(7, s)
        And i3 <- intersection(-3, s)
        And i4 <- intersection(2, s)
        And xs <- intersections(i1, i2, i3, i4)
    When i <- hit(xs)
    Then i = i4
*/
TEST(Hit, chooseLowestPositiveTime)
{
    auto s = Sphere();
    auto i1 = Intersection(5, &s);
    auto i2 = Intersection(7, &s);
    auto i3 = Intersection(-3, &s);
    auto i4 = Intersection(2, &s);
    auto xs = intersections({i1, i2, i3, i4});

    auto i = hit(xs);
    ASSERT_EQ(i, i4);
}

/*
Scenario: Precomputing the state of an intersection
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And shape <- sphere()
        And i <- intersection(4, shape)
    When comps <- prepare_computations(i, r)
    Then comps.t = i.t
        And comps.object = i.object
        And comps.point = point(0, 0, -1)
        And comps.eyev = vector(0, 0, -1)
        And comps.normalv = vector(0, 0, -1)
*/
TEST(PrepareComputations, precomputerIntersectionState)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto shape = Sphere();
    auto i = Intersection(4, &shape);

    auto comps = prepare_computations(i, r);
    ASSERT_EQ(comps.t, i.t);
    ASSERT_EQ(comps.object, i.object);
    ASSERT_EQ(comps.point, Point(0, 0, -1));
    ASSERT_EQ(comps.eyev, Vector(0, 0, -1));
    ASSERT_EQ(comps.normalv, Vector(0, 0, -1));
}

/*
Scenario: The hit, when an intersection occurs on the outside
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And shape <- sphere()
        And i <- intersection(4, shape)
    When comps <- prepare_computations(i, r)
    Then comps.inside = false
*/
TEST(PrepareComputations, detectOutsideIntersection)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto shape = Sphere();
    auto i = Intersection(4, &shape);

    auto comps = prepare_computations(i, r);
    ASSERT_EQ(comps.inside, false);
}

/*
Scenario: The hit, when an intersection occurs on the inside
    Given r <- ray(point(0, 0, 0), vector(0, 0, 1))
        And shape <- sphere()
        And i <- intersection(1, shape)
    When comps <- prepare_computations(i, r)
    Then comps.point = point(0, 0, 1)
        And comps.eyev = vector(0, 0, -1)
        And comps.inside = true
            # normal would have been (0, 0, 1), but is inverted!
        And comps.normalv = vector(0, 0, -1)
*/
TEST(PrepareComputations, detectInsideIntersection)
{
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    auto shape = Sphere();
    auto i = Intersection(1, &shape);

    auto comps = prepare_computations(i, r);
    ASSERT_EQ(comps.point, Point(0, 0, 1));
    ASSERT_EQ(comps.eyev, Vector(0, 0, -1));
    ASSERT_EQ(comps.inside, true);
    ASSERT_EQ(comps.normalv, Vector(0, 0, -1));
}

/*
Scenario: The hit should offset the point
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And shape <- sphere() with:
            | transform | translation(0, 0, 1) |
        And i <- intersection(5, shape)
    When comps <- prepare_computations(i, r)
    Then comps.over_point.z < -EPSILON/2
        And comps.point.z > comps.over_point.z
*/
TEST(PrepareComputations, hitShouldOffsetPoint)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto shape = Sphere();
    shape.transform = translation(0, 0, 1);
    auto i = Intersection(5, &shape);

    auto comps = prepare_computations(i, r);
    ASSERT_LT(comps.over_point.z(), -EPSILON / 2);
    ASSERT_GT(comps.point.z(), comps.over_point.z());
}
