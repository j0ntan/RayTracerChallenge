#include <gtest/gtest.h>
#include <math/Point.hpp>
#include <utility/Float_compare.hpp>
#include <scene/Computations.hpp>
#include <scene/Intersections.hpp>
#include <scene/Ray.hpp>
#include <scene/Transformations.hpp>

TEST(Computations, createDefault) { Computations computations; }

TEST(Computations, hasComponents) {
  Computations computations;
  double time = computations.t;
  const Sphere *sphere = computations.object;
  Point point = computations.point;
  Vector eye = computations.eyev;
  Vector normal = computations.normalv;
  bool inside = computations.inside;
}

bool operator==(const Sphere &lhs, const Sphere &rhs) {
  return lhs.radius() == rhs.radius() && lhs.origin() == rhs.origin() &&
         lhs.material() == rhs.material() &&
         lhs.transformation() == rhs.transformation();
}

TEST(Precompute, precomputeStateOfIntersection) {
  auto r = Ray(Point{0, 0, -5}, Vector{0, 0, 1});
  auto shape = Sphere();
  auto i = Intersection(4, shape);
  Computations comps = prepare_computations(i, r);
  ASSERT_EQ(comps.t, i.time());
  ASSERT_EQ(*comps.object, i.object());
  ASSERT_EQ(comps.point, (Point{0, 0, -1}));
  ASSERT_EQ(comps.eyev, (Vector{0, 0, -1}));
  ASSERT_EQ(comps.normalv, (Vector{0, 0, -1}));
}

TEST(Precompute, intersectsOnOutside) {
  auto r = Ray(Point{0, 0, -5}, Vector{0, 0, 1});
  auto shape = Sphere();
  auto i = Intersection(4, shape);
  auto comps = prepare_computations(i, r);
  ASSERT_FALSE(comps.inside);
}

TEST(Precompute, intersectsOnInside) {
  auto r = Ray(Point{0, 0, 0}, Vector{0, 0, 1});
  auto shape = Sphere();
  auto i = Intersection(1, shape);
  auto comps = prepare_computations(i, r);
  ASSERT_EQ(comps.point, (Point{0, 0, 1}));
  ASSERT_EQ(comps.eyev, (Vector{0, 0, -1}));
  ASSERT_TRUE(comps.inside);
  ASSERT_EQ(comps.normalv, (Vector{0, 0, -1}));
}

TEST(Offset, hitShouldOffsetPoint) {
  auto r = Ray(Point{0, 0, -5}, Vector{0, 0, 1});
  Sphere shape;
  shape.set_transformation(translate(0, 0, 1));
  auto i = Intersection(5, shape);
  auto comps = prepare_computations(i, r);
  ASSERT_LT(comps.over_point.z(), -EPSILON / 2);
  ASSERT_GT(comps.point.z(), comps.over_point.z());
}
