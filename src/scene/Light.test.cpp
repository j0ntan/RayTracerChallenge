#include <gtest/gtest.h>
#include <scene/Light.hpp>

TEST(Light, constructWithPointAndColor) { Light light{Point(), Color()}; }

TEST(Light, accessPosition) {
  const Light light{Point(), Color()};
  light.position;
}

TEST(Light, positionIsAPoint) {
  const Light light{Point(), Color()};
  const Point position = light.position;
}

TEST(Light, positionMatchesGivenValue) {
  Point position(1, 2, 3);
  Light light{position, Color()};
  ASSERT_EQ(light.position, position);
}

TEST(Light, accessIntensity) {
  const Light light{Point(), Color()};
  light.intensity;
}

TEST(Light, intensityIsAColor) {
  const Light light{Point(), Color()};
  const Color intensity = light.intensity;
}

TEST(Light, intensityMatchesGivenValue) {
  Point position(1, 2, 3);
  const Color intensity(1, 1, 1);
  Light light{position, intensity};
  ASSERT_EQ(light.intensity, intensity);
}
