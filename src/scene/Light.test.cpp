#include <gtest/gtest.h>
#include <scene/Light.hpp>

TEST(LightConstructor, constructWithPointAndColor) {
  Light light{Point(), Color()};
}

TEST(LightPosition, accessPosition) {
  Light light{Point(), Color()};
  Point position = light.POSITION;
}

TEST(LightPosition, matchInitializedPosition) {
  Point position(1, 2, 3);
  Light light{position, Color()};
  ASSERT_EQ(light.POSITION, position);
}

TEST(LightIntensity, accessIntensity) {
  Light light{Point(), Color()};
  Color intensity = light.INTENSITY;
}

TEST(LightIntensity, matchInitializedIntensity) {
  Color intensity(1, 1, 1);
  Light light{Point(), intensity};
  ASSERT_EQ(light.INTENSITY, intensity);
}
