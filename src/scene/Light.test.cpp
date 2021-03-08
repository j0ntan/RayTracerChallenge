#include <gtest/gtest.h>
#include <scene/Light.hpp>

TEST(Light, constructWithPointAndColor) { Light light(Point(), Color()); }

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
