#include <World/PointLight.hpp>
#include <gtest/gtest.h>

/*
Scenario: A point light has a position and intensity
    Given intensity <- color(1, 1, 1)
        And position <- point(0, 0, 0)
    When light <- point_light(position, intensity)
    Then light.position = position
        And light.intensity = intensity
*/
TEST(LightComponents, hasPositionAndIntensity)
{
    auto intensity = Color(1, 1, 1);
    auto position = Point(0, 0, 0);

    auto light = PointLight(position, intensity);
    ASSERT_EQ(light.position, position);
    ASSERT_EQ(light.intensity, intensity);
}
