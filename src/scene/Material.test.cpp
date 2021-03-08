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

TEST(Material, accessLightReflectionValues) {
  Material m;
  double ambient = m.ambient;
  double diffuse = m.diffuse;
  double specular = m.specular;
  double shininess = m.shininess;
}

TEST(Material, defaultLightReflectionValues) {
  Material m;
  ASSERT_FLOAT_EQ(m.ambient, 0.1);
  ASSERT_FLOAT_EQ(m.diffuse, 0.9);
  ASSERT_FLOAT_EQ(m.specular, 0.9);
  ASSERT_FLOAT_EQ(m.shininess, 200);
}

TEST(Material, changeLightReflectionValues) {
  Material m;
  m.ambient = 0.2;
  m.diffuse = 0.3;
  m.specular = 0.4;
  m.shininess = 234.567;

  ASSERT_FLOAT_EQ(m.ambient, 0.2);
  ASSERT_FLOAT_EQ(m.diffuse, 0.3);
  ASSERT_FLOAT_EQ(m.specular, 0.4);
  ASSERT_FLOAT_EQ(m.shininess, 234.567);
}

TEST(Material, isComparable) {
  Material m1, m2;
  bool same_material = m1 == m2;
  bool not_same_material = m1 != m2;
}

TEST(Material, compareMaterials) {
  Material m1, m2;
  ASSERT_EQ(m1, m2);
  m2.ambient = 0.123;
  ASSERT_NE(m1, m2);
  m2.ambient = m1.ambient;
  ASSERT_EQ(m1, m2);
  m2.color = Color(0, 0, 0);
  ASSERT_NE(m1, m2);
}
