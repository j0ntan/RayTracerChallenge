#include <gtest/gtest.h>
#include <scene/Lighting.hpp>

TEST(Lighting, callFunction) {
  lighting(Material(), Light(Point(), Color()), Point(), Vector(), Vector());
}

TEST(Lighting, returnsColor) {
  Color color = lighting(Material(), Light(Point(), Color()), Point(), Vector(),
                         Vector());
}
