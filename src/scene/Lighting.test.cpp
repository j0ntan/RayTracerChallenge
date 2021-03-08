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
