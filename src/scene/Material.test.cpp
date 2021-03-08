#include <gtest/gtest.h>
#include <scene/Material.hpp>

TEST(Material, defaultConstruct) { Material m; }

TEST(Material, accessColor) {
  Material m;
  Color color = m.color;
}

TEST(Material, defaultColorIsWhite) {
  Material m;
  ASSERT_EQ(m.color, Color(1, 1, 1));
}

TEST(Material, changeColor) {
  Material m;
  ASSERT_EQ(m.color, Color(1, 1, 1));
  m.color = Color(1, 0, 0);
  ASSERT_EQ(m.color, Color(1, 0, 0));
}
