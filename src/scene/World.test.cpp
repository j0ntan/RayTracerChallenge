#include <gtest/gtest.h>
#include <scene/Transformations.hpp>
#include <scene/World.hpp>

TEST(World, defaultConstruct) { World w; }

TEST(World, initialWorldIsEmpty) {
  World w;
  ASSERT_TRUE(w.objects().empty());
  ASSERT_TRUE(w.light_sources().empty());
}

TEST(defaultWorld, generateDefaultWorld) { World w = default_world(); }

TEST(defaultWorld, hasDefaultProperties) {
  auto w = default_world();
  ASSERT_EQ(w.objects().size(), 2);
  ASSERT_EQ(w.light_sources().size(), 1);
}

bool operator==(const Sphere &lhs, const Sphere &rhs) {
  return lhs.origin() == rhs.origin() && lhs.radius() == rhs.radius() &&
         lhs.transformation() == rhs.transformation() &&
         lhs.material() == rhs.material();
}

bool operator==(const Light &lhs, const Light &rhs) {
  return lhs.position == rhs.position && lhs.intensity == rhs.intensity;
}

TEST(defaultWorld, matchesDefaultConfiguration) {
  const Light light{Point{-10, 10, -10}, Color{1, 1, 1}};
  Sphere s1;
  Material material;
  material.color = Color{0.8, 1.0, 0.6};
  material.diffuse = 0.7;
  material.specular = 0.2;
  s1.set_material(material);
  Sphere s2;
  s2.set_transformation(scale(0.5, .5, .5));

  auto w = default_world();
  const auto w_light = w.light_sources().front();
  const auto w_s1 = w.objects()[1], w_s2 = w.objects()[0];
  ASSERT_EQ(w_light, light);
  ASSERT_EQ(w_s1, s1);
  ASSERT_EQ(w_s2, s2);
}
