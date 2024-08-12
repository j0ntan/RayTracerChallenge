#include <gtest/gtest.h>
#include <scene/Computations.hpp>
#include <scene/Intersection.hpp>
#include <scene/Ray.hpp>
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

TEST(intersectWorld, intersectDefaultWord) {
  auto w = default_world();
  auto r = Ray(Point{0, 0, -5}, Vector{0, 0, 1});
  std::vector<Intersection> xs = intersect_world(w, r);
  ASSERT_EQ(xs.size(), 4);
  ASSERT_EQ(xs[0].time(), 4);
  ASSERT_EQ(xs[1].time(), 4.5);
  ASSERT_EQ(xs[2].time(), 5.5);
  ASSERT_EQ(xs[3].time(), 6);
}

TEST(Shading, shadeAnIntersection) {
  auto w = default_world();
  auto r = Ray{Point{0, 0, -5}, Vector{0, 0, 1}};
  auto shape = w.objects().back();
  auto i = Intersection(4, shape);
  auto comps = prepare_computations(i, r);
  Color c = shade_hit(w, comps);
  ASSERT_EQ(c, (Color{.38066, .47583, .2855}));
}

TEST(Shading, shadeAnIntersectionFromInside) {
  auto w = default_world();
  w.clear_light_sources();
  w.add_light_source(Light{Point{0, .25, 0}, Color{1, 1, 1}});
  auto r = Ray{Point{0, 0, 0}, Vector{0, 0, 1}};
  auto shape = w.objects().front();
  auto i = Intersection(.5, shape);
  auto comps = prepare_computations(i, r);
  Color c = shade_hit(w, comps);
  ASSERT_EQ(c, (Color{.90498, .90498, .90498}));
}

TEST(ColorAt, colorForMiss) {
  auto w = default_world();
  auto r = Ray{Point{0, 0, -5}, Vector{0, 1, 0}};
  Color c = color_at(w, r);
  ASSERT_EQ(c, (Color{}));
}

TEST(ColorAt, colorOnHit) {
  auto w = default_world();
  auto r = Ray{Point{0, 0, -5}, Vector{0, 0, 1}};
  Color c = color_at(w, r);
  ASSERT_EQ(c, (Color{.38066, .47583, .2855}));
}

TEST(ColorAt, colorWithIntersectionBehindRay) {
  auto w = default_world();
  auto outer = w.objects().back();
  auto outer_material = outer.material();
  outer_material.ambient = 1;
  outer.set_material(outer_material);
  auto inner = w.objects().front();
  auto inner_material = inner.material();
  inner_material.ambient = 1;
  inner.set_material(inner_material);
  w.clear_spheres();
  w.add_sphere(inner);
  w.add_sphere(outer);
  auto r = Ray{Point{0, 0, .75}, Vector{0, 0, -1}};
  Color c = color_at(w, r);
  ASSERT_EQ(c, inner.material().color);
}

TEST(AddingShadows, callShadowDetectFunction) {
  bool result = is_shadowed(default_world(), Point());
}

TEST(AddingShadows, noShadowWhenNothingInBetween) {
  auto w = default_world();
  auto p = Point(0, 10, 0);
  ASSERT_FALSE(is_shadowed(w, p));
}

TEST(AddingShadows, shadowCastOnPointBehindObject) {
  auto w = default_world();
  auto p = Point(10, -10, 10);
  ASSERT_TRUE(is_shadowed(w, p));
}

TEST(AddingShadows, noShadowWhenBehindTheLight) {
  auto w = default_world();
  auto p = Point(-20, 20, -20);
  ASSERT_FALSE(is_shadowed(w, p));
}

TEST(AddingShadows, noShadowWhenObjectBehindPoint) {
  auto w = default_world();
  auto p = Point(-2, 2, -2);
  ASSERT_FALSE(is_shadowed(w, p));
}
