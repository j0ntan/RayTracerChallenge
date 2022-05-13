#include <gtest/gtest.h>
#include <scene/Computations.hpp>

TEST(Computations, createDefault) { Computations computations; }

TEST(Computations, hasComponents) {
  Computations computations;
  double time = computations.t;
  const Sphere *sphere = computations.object;
  Point point = computations.point;
  Vector eye = computations.eyev;
  Vector normal = computations.normalv;
}
