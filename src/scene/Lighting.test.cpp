#include <cmath>
#include <gtest/gtest.h>
#include <scene/Lighting.hpp>

class Lighting_F : public ::testing::Test {
public:
  const Material default_material;
  const Point illuminated;
  const Color light_color = Color(1, 1, 1);
  const Vector surface_normal = Vector(0, 0, -1);
};

TEST_F(Lighting_F, callFunction) {
  lighting(Material(), Light(Point(), Color()), Point(), Vector(), Vector());
}

TEST_F(Lighting_F, returnsColor) {
  Color color = lighting(Material(), Light(Point(), Color()), Point(), Vector(),
                         Vector());
}

TEST_F(Lighting_F, eyeBetweenLightAndSurface) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 0, -10), light_color);
  auto result = lighting(default_material, light_source, illuminated, eye,
                         surface_normal);
  ASSERT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST_F(Lighting_F, eyeAt45DegreesBetweenLightAndSurface) {
  auto eye = Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  auto light_source = Light(Point(0, 0, -10), light_color);
  auto result = lighting(default_material, light_source, illuminated, eye,
                         surface_normal);
  ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST_F(Lighting_F, eyeOppositeSurfaceWithLightOffsetBy45Degrees) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 10, -10), light_color);
  auto result = lighting(default_material, light_source, illuminated, eye,
                         surface_normal);
  ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST_F(Lighting_F, eyeInPathOfReflectionVector) {
  auto eye = Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  auto light_source = Light(Point(0, 10, -10), light_color);
  auto result = lighting(default_material, light_source, illuminated, eye,
                         surface_normal);
  ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST_F(Lighting_F, lightBehindTheSurface) {
  auto eye = Vector(0, 0, -1);
  auto light_source = Light(Point(0, 0, 10), light_color);
  auto result = lighting(default_material, light_source, illuminated, eye,
                         surface_normal);
  ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}
