#include <gtest/gtest.h>
#include <math/Intersections.hpp>

TEST(Intersections, callIntersect) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 0));
  Sphere s;
  intersect(s, r);
}

TEST(Intersections, getVectorOfTimeValues) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 0));
  Sphere s;
  std::vector<double> xs = intersect(s, r);
}
