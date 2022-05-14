#include <gtest/gtest.h>
#include <math/Point.hpp>
#include <scene/Computations.hpp>
#include <scene/Intersections.hpp>
#include <scene/Ray.hpp>

TEST(Computations, createDefault) { Computations computations; }

TEST(Computations, hasComponents) {
  Computations computations;
  double time = computations.t;
  const Sphere *sphere = computations.object;
  Point point = computations.point;
  Vector eye = computations.eyev;
  Vector normal = computations.normalv;
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
