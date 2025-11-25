#include <cmath>
#include <memory>
#include <Interactions/Interactions.hpp>
#include <Float_compare.hpp>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Math/Plane.hpp>
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

/*
Scenario: Precomputing the reflection vector
    Given shape <- plane()
        And r <- ray(point(0, 1, -1), vector(0, -sqrt(2)/2, sqrt(2)/2))
        And i <- intersection(sqrt(2), shape)
    When comps <- prepare_computations(i, r)
    Then comps.reflectv = vector(0, sqrt(2)/2, sqrt(2)/2)
*/
TEST(PrepareComputations, precomputeReflectionVector)
{
    auto shape = std::make_shared<Plane>();
    auto r = Ray(Point(0, 1, -1),
                 Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    auto i = Intersection(sqrt(2), shape.get());

    auto comps = prepare_computations(i, r);

    ASSERT_EQ(comps.reflectv, Vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
}

/*
Scenario Outline: Finding n1 and n2 at various intersections
    Given A <- glass_sphere() with:
            | transform                 | scaling(2, 2, 2) |
            | material.refractive_index | 1.5              |
        And B <- glass_sphere() with:
            | transform                 | translation(0, 0, -0.25) |
            | material.refractive_index | 2.0                      |
        And C <- glass_sphere() with:
            | transform                 | translation(0, 0, 0.25) |
            | material.refractive_index | 2.5                     |
        And r <- ray(point(0, 0, -4), vector(0, 0, 1))
        And xs <- intersections(2:A, 2.75:B, 3.25:C, 4.75:B, 5.25:C, 6:A)
    When comps <- prepare_computations(xs[<index>], r, xs)
    Then comps.n1 = <n1>
        And comps.n2 = <n2>

    Examples:
        | index | n1  | n2  |
        | 0     | 1.0 | 1.5 |
        | 1     | 1.5 | 2.0 |
        | 2     | 2.0 | 2.5 |
        | 3     | 2.5 | 2.5 |
        | 4     | 2.5 | 1.5 |
        | 5     | 1.5 | 1.0 |
*/
TEST(RefractiveIndex, findN1AndN2AtIntersections)
{
    auto A = glass_sphere();
    A.transform = scaling(2, 2, 2);
    A.material.refractive_index = 1.5;
    auto B = glass_sphere();
    B.transform = translation(0, 0, -0.25);
    B.material.refractive_index = 2.0;
    auto C = glass_sphere();
    C.transform = translation(0, 0, 0.25);
    C.material.refractive_index = 2.5;
    auto r = Ray(Point(0, 0, -4), Vector(0, 0, 1));
    auto testing_intersections = std::vector<Intersection>{
        {2, &A}, {2.75, &B}, {3.25, &C}, {4.75, &B}, {5.25, &C}, {6, &A}};
    auto xs = intersections(testing_intersections);

    std::vector<double> n1_vals{1.0, 1.5, 2.0, 2.5, 2.5, 1.5},
        n2_vals{1.5, 2.0, 2.5, 2.5, 1.5, 1.0};
    for (int i = 0; i < n1_vals.size(); ++i)
    {
        auto comps = prepare_computations(xs[i], r, xs);

        ASSERT_FLOAT_EQ(comps.n1, n1_vals[i]);
        ASSERT_FLOAT_EQ(comps.n2, n2_vals[i]);
    }
}

/*
Scenario: The under point is offset below the surface
    Given r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And shape <- glass_sphere() with:
            | transform | translation(0, 0, 1) |
        And i <- intersection(5, shape)
        And xs <- intersections(i)
    When comps <- prepare_computations(i, r, xs)
    Then comps.under_point.z > EPSILON/2
        And comps.point.z < comps.under_point.z
*/
TEST(UnderPoint, pointIsOffsetBelowTheSurface)
{

    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto shape = glass_sphere();
    shape.transform = translation(0, 0, 1);
    auto i = Intersection(5, &shape);
    auto xs = intersections({i});

    auto comps = prepare_computations(i, r, xs);

    ASSERT_GT(comps.under_point.z(), EPSILON / 2);
    ASSERT_LT(comps.point.z(), comps.under_point.z());
}

/*
Scenario: The refracted color with an opaque surface
    Given w <- default_world()
        And shape <- the first object in w
        And r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And xs <- intersections(4:shape, 6:shape)
    When comps <- prepare_computations(xs[0], r, xs)
        And c <- refracted_color(w, comps, 5)
    Then c = color(0, 0, 0)
*/
TEST(RefractedColor, colorWithAnOpaqueSurface)
{
    auto w = default_world();
    const Shape *shape = w.objects.front().get();
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = intersections({{4, shape}, {6, shape}});

    auto comps = prepare_computations(xs[0], r, xs);
    auto c = refracted_color(w, comps, 5);

    ASSERT_EQ(c, Color(0, 0, 0));
}

/*
Scenario: The refracted color at the maximum recursive depth
    Given w <- default_world()
        And shape <- the first object in w
        And shape has:
            | material.transparency | 1.0 |
            | material.refractive_index | 1.5 |
        And r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And xs <- intersections(4:shape, 6:shape)
    When comps <- prepare_computations(xs[0], r, xs)
        And c <- refracted_color(w, comps, 0)
    Then c = color(0, 0, 0)
*/
TEST(RefractedColor, colorAtMaximumRecursiveDepth)
{
    auto w = default_world();
    Shape *shape = w.objects.front().get();
    shape->material.transparency = 1.0;
    shape->material.refractive_index = 1.5;
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = intersections({{4, shape}, {6, shape}});

    auto comps = prepare_computations(xs[0], r, xs);
    auto c = refracted_color(w, comps, 0);

    ASSERT_EQ(c, Color(0, 0, 0));
}

/*
Scenario: The Schlick approximation under total internal reflection
    Given shape <- glass_sphere()
        And r <- ray(point(0, 0, sqrt(2)/2), vector(0, 1, 0))
        And xs <- intersections(-sqrt(2)/2:shape, sqrt(2)/2:shape)
    When comps <- prepare_computations(xs[1], r, xs)
        And reflectance <- schlick(comps)
    Then reflectance = 1.0
*/
TEST(FresnelEffect, schlickApproxUnderTotalInternalReflection)
{
    auto shape = glass_sphere();
    auto r = Ray(Point(0, 0, std::sqrt(2) / 2), Vector(0, 1, 0));
    auto xs = intersections(
        {{-std::sqrt(2) / 2, &shape}, {std::sqrt(2) / 2, &shape}});

    auto comps = prepare_computations(xs[1], r, xs);
    auto reflectance = schlick(comps);

    ASSERT_FLOAT_EQ(reflectance, 1.0);
}

/*
Scenario: The Schlick approximation with a perpendicular viewing angle
    Given shape <- glass_sphere()
        And r <- ray(point(0, 0, 0), vector(0, 1, 0))
        And xs <- intersections(-1:shape, 1:shape)
    When comps <- prepare_computations(xs[1], r, xs)
        And reflectance <- schlick(comps)
    Then reflectance = 0.04
*/
TEST(FresnelEffect, schlickApproxWithPerpendicularViewingAngle)
{
    auto shape = glass_sphere();
    auto r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
    auto xs = intersections({{-1, &shape}, {1, &shape}});

    auto comps = prepare_computations(xs[1], r, xs);
    auto reflectance = schlick(comps);

    ASSERT_FLOAT_EQ(reflectance, 0.04);
}

/*
Scenario: The Schlick approximation with small angle and n2 > n1
    Given shape <- glass_sphere()
        And r <- ray(point(0, 0.99, -2), vector(0, 0, 1))
        And xs <- intersections(1.8589:shape)
    When comps <- prepare_computations(xs[0], r, xs)
        And reflectance <- schlick(comps)
    Then reflectance = 0.48873
*/
TEST(FresnelEffect, schlickApproxWithSmallAngleAndN2GTN1)
{
    auto shape = glass_sphere();
    auto r = Ray(Point(0, 0.99, -2), Vector(0, 0, 1));
    auto xs = intersections({{1.8589, &shape}});

    auto comps = prepare_computations(xs[0], r, xs);
    auto reflectance = schlick(comps);

    // rounding error with ASSERT_FLOAT_EQ
    ASSERT_NEAR(reflectance, 0.48873, EPSILON);
}
