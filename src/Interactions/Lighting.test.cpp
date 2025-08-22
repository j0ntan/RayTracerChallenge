#include <numbers>
#include <Lighting.hpp>
#include <gtest/gtest.h>

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with the eye between the light and the surface
    Given eyev <- vector(0, 0, -1)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 0, -10), color(1, 1, 1))
    When result <- lighting(m, light, position, eyev, normalv)
    Then result = color(1.9, 1.9, 1.9)
*/
TEST(Lighting, eyeBetweenLightAndSurface)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));

    auto result = lighting(m, light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.9, 1.9, 1.9));
}

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with the eye between light and surface, eye offset 45°
    Given eyev <- vector(0, sqrt(2) / 2, -sqrt(2) /2)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 0, -10), color(1, 1, 1))
    When result <- lighting(m, light, position, eyev, normalv)
    Then result = color(1.0, 1.0, 1.0)
*/
TEST(Lighting, eyeBetweenLightAndSurfaceOffset45Degrees)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, std::numbers::sqrt2 / 2, -std::numbers::sqrt2 / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));

    auto result = lighting(m, light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with eye opposite surface, light offset 45°
    Given eyev <- vector(0, 0, -1)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 10, -10), color(1, 1, 1))
    When result <- lighting(m, light, position, eyev, normalv)
    Then result = color(0.7364, 0.7364, 0.7364)
*/
TEST(Lighting, eyeOppositeSurfaceOffset45Degrees)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));

    auto result = lighting(m, light, position, eyev, normalv);
    ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with eye in the path of the reflection vector
    Given eyev <- vector(0, -sqrt(2) / 2, -sqrt(2) /2)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 10, -10), color(1, 1, 1))
    When result <- lighting(m, light, position, eyev, normalv)
    Then result = color(1.6364, 1.6364, 1.6364)
*/
TEST(Lighting, eyeInPathOfReflectionVector)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, -std::numbers::sqrt2 / 2, -std::numbers::sqrt2 / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));

    auto result = lighting(m, light, position, eyev, normalv);
    ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with the light behind the surface
    Given eyev <- vector(0, 0, -1)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 0, 10), color(1, 1, 1))
    When result <- lighting(m, light, position, eyev, normalv)
    Then result = color(0.1, 0.1, 0.1)
*/
TEST(Lighting, lightBehindSurface)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, 10), Color(1, 1, 1));

    auto result = lighting(m, light, position, eyev, normalv);
    ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

/*
Background:
    Given m <- material()
        And position <- point(0, 0, 0)
Scenario: Lighting with the surface in shadow
    Given eyev <- vector(0, 0, -1)
        And normalv <- vector(0, 0, -1)
        And light <- point_light(point(0, 0, -10), color(1, 1, 1))
        And in_shadow <- true
    When result <- lighting(m, light, position, eyev, normalv, in_shadow)
    Then result = color(0.1, 0.1, 0.1)
*/
TEST(Lighting, surfaceInShadow)
{
    auto m = Material();
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto in_shadow = true;

    auto result = lighting(m, light, position, eyev, normalv, in_shadow);
    ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

/*
Scenario: Lighting with a pattern applied
    Given m.pattern ← stripe_pattern(color(1, 1, 1), color(0, 0, 0))
        And m.ambient ← 1
        And m.diffuse ← 0
        And m.specular ← 0
        And eyev ← vector(0, 0, -1)
        And normalv ← vector(0, 0, -1)
        And light ← point_light(point(0, 0, -10), color(1, 1, 1))
    When c1 ← lighting(m, light, point(0.9, 0, 0), eyev, normalv, false)
        And c2 ← lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)
    Then c1 = color(1, 1, 1)
        And c2 = color(0, 0, 0)
*/
TEST(Lighting, patternApplied)
{
    Material m;

    m.pattern = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));

    auto c1 = lighting(m, light, Point(0.9, 0, 0), eyev, normalv, false);
    auto c2 = lighting(m, light, Point(1.1, 0, 0), eyev, normalv, false);

    ASSERT_EQ(c1, Color(1, 1, 1));
    ASSERT_EQ(c2, Color(0, 0, 0));
}
