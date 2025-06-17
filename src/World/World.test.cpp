#include <algorithm>
#include <World/World.hpp>
#include <Math/Transformations.hpp>
#include <MaterialCmp.hpp>
#include <Interactions.hpp>
#include <gtest/gtest.h>

/**
 * @brief Overload the == operator for PointLight comparison
 *
 */
bool operator==(const PointLight &lhs, const PointLight &rhs)
{
    return lhs.position == rhs.position && lhs.intensity == rhs.intensity;
}

/**
 * @brief Overload the == operator for Sphere comparison
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator==(const Sphere &lhs, const Sphere &rhs)
{
    return lhs.material == rhs.material && lhs.transform == rhs.transform;
}

/**
 * @brief Checks if a sphere is contained in the world
 *
 * @param world The world to check
 * @param sphere The sphere to check for
 * @return true if the sphere is found in the world
 * @return false if the sphere is not found
 */
bool contains_sphere(const World &world, const Sphere &sphere)
{
    return std::find_if(world.objects.cbegin(), world.objects.cend(),
                        [&](const std::shared_ptr<Sphere> &s)
                        { return (*s) == sphere; }) != world.objects.end();
}

/*
Scenario: Creating a world
    Given w <- world()
    Then w contains no objects
        And w has no light source
*/
TEST(World, defaultWorldIsEmpty)
{
    auto w = World();

    ASSERT_TRUE(w.objects.empty());
    ASSERT_EQ(w.light, nullptr);
}

/*
Scenario: The default world
    Given light <- point_light(point(-10, 10, -10), color(1, 1, 1))
        And s1 <- sphere() with:
            | material.color    | (0.8, 1.0, 0.6) |
            | material.diffuse  | 0.7             |
            | material.specular | 0.2             |
        And s2 <- sphere() with:
            | transform | scaling(0.5, 0.5, 0.5) |
    When w <- default_world()
    Then w.light = light
        And w contains s1
        And w contains s2
*/
TEST(WorldDefault, createSpecifiedDefaultWorld)
{
    auto light = PointLight(Point(-10, 10, -10), Color(1, 1, 1));
    auto s1 = Sphere();
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    auto s2 = Sphere();
    s2.transform = scaling(0.5, 0.5, 0.5);

    auto w = default_world();
    ASSERT_EQ(*w.light, light);
    ASSERT_TRUE(contains_sphere(w, s1));
    ASSERT_TRUE(contains_sphere(w, s2));
}

/*
Scenario: Intersect a world with a ray
    Given w <- default_world()
        And r <- ray(point(0, 0, -5), vector(0, 0, 1))
    When xs <- intersect_world(w, r)
    Then xs.count = 4
        And xs[0].t = 4
        And xs[1].t = 4.5
        And xs[2].t = 5.5
        And xs[3].t = 6
*/
TEST(WorldDefault, intersectDefaultWithRay)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));

    auto xs = intersect_world(w, r);
    ASSERT_EQ(xs.size(), 4);
    ASSERT_EQ(xs[0].t, 4);
    ASSERT_EQ(xs[1].t, 4.5);
    ASSERT_EQ(xs[2].t, 5.5);
    ASSERT_EQ(xs[3].t, 6);
}

/*
Scenario: Shading an intersection
    Given w <- default_world()
        And r <- ray(point(0, 0, -5), vector(0, 0, 1))
        And shape <- the first object in w
        And i <- intersection(4, shape)
    When comps <- prepare_computations(i, r)
        And c <- shade_hit(w, comps)
    Then c = color(0.38066, 0.47583, 0.2855)
*/
TEST(shade_hit, shadeAnIntersection)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto shape = w.objects.front();
    auto i = Intersection(4, shape.get());

    auto comps = prepare_computations(i, r);
    auto c = shade_hit(w, comps);
    ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

/*
Scenario: Shading an intersection from the inside
    Given w <- default_world()
        And w.light <- point_light(point(0, 0.25, 0), color(1, 1, 1))
        And r <- ray(point(0, 0, 0), vector(0, 0, 1))
        And shape <- the second object in w
        And i <- intersection(0.5, shape)
    When comps <- prepare_computations(i, r)
        And c <- shade_hit(w, comps)
    Then c = color(0.90498, 0.90498, 0.90498)
*/
TEST(shade_hit, shadeIntersectionFromInside)
{
    auto w = default_world();
    w.light = std::make_shared<PointLight>(Point(0, 0.25, 0), Color(1, 1, 1));
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    auto shape = w.objects.back();
    auto i = Intersection(0.5, shape.get());

    auto comps = prepare_computations(i, r);
    auto c = shade_hit(w, comps);
    ASSERT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

/*
Scenario: The color when a ray misses
    Given w <- default_world()
        And r <- ray(point(0, 0, -5), vector(0, 1, 0))
    When c <- color_at(w, r)
    Then c = color(0, 0, 0)
*/
TEST(color_at, colorWhenRayMisses)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, -5), Vector(0, 1, 0));
    auto c = color_at(w, r);
    ASSERT_EQ(c, Color(0, 0, 0));
}

/*
Scenario: The color when a ray hits
    Given w <- default_world()
        And r <- ray(point(0, 0, -5), vector(0, 0, 1))
    When c <- color_at(w, r)
    Then c = color(0.38066, 0.47583, 0.2855)
*/
TEST(color_at, colorWhenRayHits)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto c = color_at(w, r);
    ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

/*
Scenario: The color with an intersection behind the ray
    Given w <- default_world()
        And outer <- the first object in w
        And outer.material.ambient <- 1
        And inner <- the second object in w
        And inner.material.ambient <- 1
        And r <- ray(point(0, 0, 0.75), vector(0, 0, -1))
    When c <- color_at(w, r)
    Then c = inner.material.color
*/
TEST(color_at, colorWithIntersectionBehindRay)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto c = color_at(w, r);
    ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

/*
Scenario: There is no shadow when nothing is collinear with point and light
    Given w <- default_world()
        And p <- point(0, 10, 0)
    Then is_shadowed(w, p) is false
*/
TEST(is_shadowed, nothingBetweenPointAndLight)
{
    auto w = default_world();
    auto p = Point(0, 10, 0);

    ASSERT_FALSE(is_shadowed(w, p));
}

/*
Scenario: The shadow when an object is between the point and the light
    Given w <- default_world()
        And p <- point(10, -10, 10)
    Then is_shadowed(w, p) is true
*/
TEST(is_shadowed, objectBetweenPointAndLight)
{
    auto w = default_world();
    auto p = Point(10, -10, 10);

    ASSERT_TRUE(is_shadowed(w, p));
}

/*
Scenario: There is no shadow when an object is behind the light
    Given w <- default_world()
        And p <- point(-20, 20, -20)
    Then is_shadowed(w, p) is false
*/
TEST(is_shadowed, objectBehindLight)
{
    auto w = default_world();
    auto p = Point(-20, 20, -20);

    ASSERT_FALSE(is_shadowed(w, p));
}

/*
Scenario: There is no shadow when an object is behind the point
    Given w <- default_world()
        And p <- point(-2, 2, -2)
    Then is_shadowed(w, p) is false
*/
TEST(is_shadowed, objectBehindPoint)
{
    auto w = default_world();
    auto p = Point(-2, 2, -2);

    ASSERT_FALSE(is_shadowed(w, p));
}

/*
Scenario: shade_hit() is given an intersection in shadow
    Given w <- world()
        And w.light <- point_light(point(0, 0, -10), color(1, 1, 1))
        And s1 <- sphere()
        And s1 is added to w
        And s2 <- sphere() with:
            | transform | translation(0, 0, 10) |
        And s2 is added to w
        And r <- ray(point(0, 0, 5), vector(0, 0, 1))
        And i <- intersection(4, s2)
    When comps <- prepare_computations(i, r)
        And c <- shade_hit(w, comps)
    Then c = color(0.1, 0.1, 0.1)
*/
TEST(shade_hit, givenIntersectionInShadow)
{
    auto w = World();
    w.light =
        std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));
    auto s1 = Sphere();
    w.objects.push_back(std::make_shared<Sphere>(s1));
    auto s2 = Sphere();
    s2.transform = translation(0, 0, 10);
    w.objects.push_back(std::make_shared<Sphere>(s2));
    auto r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    auto i = Intersection(4, w.objects.back().get());

    auto comps = prepare_computations(i, r);
    auto c = shade_hit(w, comps);
    ASSERT_EQ(c, Color(0.1, 0.1, 0.1));
}
