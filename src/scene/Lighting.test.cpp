#include <cmath>

#include <gtest/gtest.h>

#include <scene/Lighting.hpp>

#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Light.hpp>
#include <scene/Material.hpp>

class Lighting_F : public ::testing::Test {
public:
  const Material DEFAULT_MATERIAL;
  const Point ILLUMINATED;
  const Color LIGHT_COLOR = Color(1, 1, 1);
  const Vector SURFACE_NORMAL = Vector(0, 0, -1);
};

TEST_F(Lighting_F, callFunction) {
  Color color = lighting(Material(), Light(Point(), Color()), Point(), Vector(),
                         Vector());
}

TEST_F(Lighting_F, eyeBetweenLightAndSurface) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 0, -10), LIGHT_COLOR);
  Color result = lighting(DEFAULT_MATERIAL, light_source, ILLUMINATED, eye,
                          SURFACE_NORMAL),
        expected(1.9, 1.9, 1.9);

  ASSERT_EQ(result, expected);
}

TEST_F(Lighting_F, eyeAt45DegreesBetweenLightAndSurface) {
  auto eye = Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  auto light_source = Light(Point(0, 0, -10), LIGHT_COLOR);
  auto result = lighting(DEFAULT_MATERIAL, light_source, ILLUMINATED, eye,
                         SURFACE_NORMAL);
  ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST_F(Lighting_F, eyeOppositeSurfaceWithLightOffsetBy45Degrees) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 10, -10), LIGHT_COLOR);
  auto result = lighting(DEFAULT_MATERIAL, light_source, ILLUMINATED, eye,
                         SURFACE_NORMAL);
  ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST_F(Lighting_F, eyeInPathOfReflectionVector) {
  auto eye = Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  auto light_source = Light(Point(0, 10, -10), LIGHT_COLOR);
  auto result = lighting(DEFAULT_MATERIAL, light_source, ILLUMINATED, eye,
                         SURFACE_NORMAL);
  ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST_F(Lighting_F, lightBehindTheSurface) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 0, 10), LIGHT_COLOR);
  auto result = lighting(DEFAULT_MATERIAL, light_source, ILLUMINATED, eye,
                         SURFACE_NORMAL);
  ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST_F(Lighting_F, acceptShadowParameter) {
  auto eyev = Vector(0, 0, -1);
  auto light = Light(Point(0, 0, -10), LIGHT_COLOR);
  const bool IN_SHADOW = true;
  auto result = lighting(DEFAULT_MATERIAL, light, ILLUMINATED, eyev,
                         SURFACE_NORMAL, IN_SHADOW);
}

TEST_F(Lighting_F, includeShadowEffectForLighting) {
  auto eyev = Vector(0, 0, -1);
  auto normalv = Vector(0, 0, -1);
  auto light = Light(Point(0, 0, -10), LIGHT_COLOR);
  const bool IN_SHADOW = true;
  auto result = lighting(DEFAULT_MATERIAL, light, ILLUMINATED, eyev,
                         SURFACE_NORMAL, IN_SHADOW);
  ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}
