#include <gtest/gtest.h>
#include <scene/Material.hpp>

TEST(MaterialComponents, accessAllComponents) {
  Material material;
  Color color = material.color;
  double ambient = material.ambient;
  double diffuse = material.diffuse;
  double specular = material.specular;
  double shininess = material.shininess;
}

TEST(MaterialDefault, matchDefaultValues) {
  Material material;
  Color expected_color = Color(1, 1, 1);
  double expected_ambient = 0.1;
  double expected_diffuse = 0.9;
  double expected_specular = 0.9;
  double expected_shininess = 200;

  ASSERT_EQ(material.color, expected_color);
  ASSERT_EQ(material.ambient, expected_ambient);
  ASSERT_EQ(material.diffuse, expected_diffuse);
  ASSERT_EQ(material.specular, expected_specular);
  ASSERT_EQ(material.shininess, expected_shininess);
}

TEST(MaterialEqualityOperator, isComparable) {
  Material m1, m2;
  bool same_material = m1 == m2;
  bool not_same_material = m1 != m2;
}

TEST(MaterialEqualityOperator, equateObjectWithNegligibleDifference) {
  Material m1, m2, m3;
  m1.ambient = 0.2;
  m2.ambient = 0.20001;

  ASSERT_EQ(m1, m2);
  ASSERT_NE(m1, m3);
}
