#include <algorithm>
#include <cmath>
#include <World/World.hpp>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Math/Plane.hpp>
#include <MaterialCmp.hpp>
#include <Interactions/Interactions.hpp>
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
                        [&](const std::shared_ptr<Shape> &s)
                        { return *static_cast<Sphere *>(s.get()) ==
                                 sphere; }) != world.objects.end();
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

/*
Scenario: The reflected color for a nonreflective material
    Given w <- default_world()
        And r <- ray(point(0, 0, 0), vector(0, 0, 1))
        And shape <- the second object in w
        And shape.material.ambient <- 1
        And i <- intersection(1, shape)
    When comps <- prepare_computations(i, r)
        And color <- reflected_color(w, comps)
    Then color = color(0, 0, 0)
*/
TEST(ReflectedColor, colorForNonreflectiveMaterial)
{
    auto w = default_world();
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    auto shape = w.objects[1];
    shape->material.ambient = 1;
    auto i = Intersection(1, shape.get());

    auto comps = prepare_computations(i, r);
    auto color = reflected_color(w, comps);

    ASSERT_EQ(color, Color(0, 0, 0));
}

/*
Scenario: The reflected color for a reflective material
    Given w <- default_world()
        And shape <- plane() with:
            | material.reflective | 0.5                   |
            | transform           | translation(0, -1, 0) |
        And shape is added to w
        And r <- ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))
        And i <- intersection(sqrt(2), shape)
    When comps <- prepare_computations(i, r)
        And color <- reflected_color(w, comps)
    Then color = color(0.19032, 0.2379, 0.14274)
*/
TEST(ReflectedColor, colorForReflectiveMaterial)
{
    auto w = default_world();
    auto shape = std::make_shared<Plane>();
    shape->material.reflective = 0.5;
    shape->transform = translation(0, -1, 0);
    w.objects.push_back(shape);
    auto r = Ray(Point(0, 0, -3),
                 Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    auto i = Intersection(std::sqrt(2), shape.get());

    auto comps = prepare_computations(i, r);
    auto color = reflected_color(w, comps);

    ASSERT_EQ(color, Color(0.19032, 0.2379, 0.14274));
}

/*
Scenario: shade_hit() with a reflective material
    Given w <- default_world()
        And shape <- plane() with:
            | material.reflective | 0.5                   |
            | transform           | translation(0, -1, 0) |
        And shape is added to w
        And r <- ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))
        And i <- intersection(sqrt(2), shape)
    When comps <- prepare_computations(i, r)
        And color <- shade_hit(w, comps)
    Then color = color(0.87677, 0.92436, 0.82918)
*/
TEST(ReflectedColor, shadeHitWithReflectiveMaterial)
{
    auto w = default_world();
    auto shape = std::make_shared<Plane>();
    shape->material.reflective = 0.5;
    shape->transform = translation(0, -1, 0);
    w.objects.push_back(shape);
    auto r = Ray(Point(0, 0, -3),
                 Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    auto i = Intersection(std::sqrt(2), shape.get());

    auto comps = prepare_computations(i, r);
    auto color = shade_hit(w, comps);

    ASSERT_EQ(color, Color(0.87677, 0.92436, 0.82918));
}

/*
Scenario: color_at() with mutually reflective surfaces
    Given w <- world()
        And w.light <- point_light(point(0, 0, 0), color(1, 1, 1))
        And lower <- plane() with:
            | material.reflective | 1                     |
            | transform           | translation(0, -1, 0) |
        And lower is added to w
        And upper <- plane() with:
            | material.reflective | 1                    |
            | transform           | translation(0, 1, 0) |
        And upper is added to w
        And r <- ray(point(0, 0, 0), vector(0, 1, 0))
    Then color_at(w, r) should terminate successfully
*/
TEST(ReflectedColor, colorWithMutuallyReflectiveSurfaces)
{
    auto w = World();
    w.light = std::make_shared<PointLight>(Point(0, 0, 0), Color(1, 1, 1));
    auto lower = std::make_shared<Plane>();
    lower->material.reflective = 1;
    lower->transform = translation(0, -1, 0);
    w.objects.push_back(lower);
    auto upper = std::make_shared<Plane>();
    upper->material.reflective = 1;
    upper->transform = translation(0, 1, 0);
    w.objects.push_back(upper);
    auto r = Ray(Point(0, 0, 0), Vector(0, 1, 0));

    ASSERT_NO_THROW(color_at(w, r));
}

/*
Scenario: The reflected color at the maximum recursive depth
    Given w <- default_world()
        And shape <- plane() with:
            | material.reflective | 0.5                   |
            | transform           | translation(0, -1, 0) |
        And shape is added to w
        And r <- ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))
        And i <- intersection(sqrt(2), shape)
    When comps <- prepare_computations(i, r)
        And color <- reflected_color(w, comps, 0)
    Then color = color(0, 0, 0)
*/
TEST(ReflectedColor, reflectedColorAtMaxRecursiveDepth)
{
    auto w = default_world();
    auto shape = std::make_shared<Plane>();
    shape->material.reflective = 0.5;
    shape->transform = translation(0, -1, 0);
    w.objects.push_back(shape);
    auto r = Ray(Point(0, 0, -3),
                 Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    auto i = Intersection(std::sqrt(2), shape.get());

    auto comps = prepare_computations(i, r);
    auto color = reflected_color(w, comps, 0);

    ASSERT_EQ(color, Color(0, 0, 0));
}

/*
Scenario: The refracted color under total internal reflection
    Given w <- default_world()
        And shape <- the first object in w
        And shape has:
            | material.transparency     | 1.0 |
            | material.refractive_index | 1.5 |
        And r <- ray(point(0, 0, sqrt(2)/2), vector(0, 1, 0))
        And xs <- intersections(-sqrt(2)/2:shape, sqrt(2)/2:shape)
    # NOTE: this time you're inside the sphere, so you need
    # to look at the second intersection, xs[1], not xs[0]
    When comps <- prepare_computations(xs[1], r, xs)
        And c <- refracted_color(w, comps, 5)
    Then c = color(0, 0, 0)
*/
TEST(RefractedColor, colorUnderTotalInternalReflection)
{
    auto w = default_world();
    Shape *shape = w.objects.front().get();
    shape->material.transparency = 1.0;
    shape->material.refractive_index = 1.5;
    auto r = Ray(Point(0, 0, std::sqrt(2) / 2), Vector(0, 1, 0));
    auto xs = intersections({{-std::sqrt(2) / 2, shape}, {std::sqrt(2) / 2, shape}});

    auto comps = prepare_computations(xs[1], r, xs);
    auto c = refracted_color(w, comps, 5);

    ASSERT_EQ(c, Color(0, 0, 0));
}

/*
Scenario: The refracted color with a refracted ray
    Given w <- default_world()
        And A <- the first object in w
        And A has:
            | material.ambient | 1.0            |
            | material.pattern | test_pattern() |
        And B <- the second object in w
        And B has:
            | material.transparency | 1.0     |
            | material.refractive_index | 1.5 |
        And r <- ray(point(0, 0, 0.1), vector(0, 1, 0))
        And xs <- intersections(-0.9899:A, -0.4899:B, 0.4899:B, 0.9899:A)
    When comps <- prepare_computations(xs[2], r, xs)
        And c <- refracted_color(w, comps, 5)
    Then c = color(0, 0.99888, 0.04725)
*/
TEST(RefractedColor, colorWithARefractedRay)
{
    /**
     * @brief Concrete pattern for testing some pattern properties
     *
     */
    struct test_pattern final : public Pattern
    {
        virtual ~test_pattern() = default;

        std::unique_ptr<Pattern> clone() const override
        {
            return std::make_unique<test_pattern>(*this);
        }

        Color pattern_at(const Point &point) const override
        {
            return Color(point.x(), point.y(), point.z());
        }
    };

    auto w = default_world();
    auto A = w.objects.front().get();
    A->material.ambient = 1.0;
    A->material.pattern = std::make_unique<test_pattern>();
    auto B = w.objects.back().get();
    B->material.transparency = 1.0;
    B->material.refractive_index = 1.5;
    auto r = Ray(Point(0, 0, 0.1), Vector(0, 1, 0));
    auto xs = intersections(
        {{-0.9899, A}, {-0.4899, B}, {0.4899, B}, {0.9899, A}});

    auto comps = prepare_computations(xs[2], r, xs);
    auto c = refracted_color(w, comps, 5);

    ASSERT_EQ(c, Color(0, 0.99888, 0.04725));
}
