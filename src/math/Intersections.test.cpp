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
  std::vector<Intersection> xs = intersect(s, r);
}

TEST(Intersections, intersectSphereAtTwoPoints) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_FLOAT_EQ(xs[0].time(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].time(), 6.0);
}

TEST(Intersections, intersectSphereAtTangent) {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_FLOAT_EQ(xs[0].time(), 5.0);
  ASSERT_FLOAT_EQ(xs[1].time(), 5.0);
}

TEST(Intersections, noIntersectionOnRayMiss) {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 0);
}

TEST(Intersections, rayInsideSphere) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_FLOAT_EQ(xs[0].time(), -1.0);
  ASSERT_FLOAT_EQ(xs[1].time(), 1.0);
}

TEST(Intersections, rayBehindSphere) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_FLOAT_EQ(xs[0].time(), -6.0);
  ASSERT_FLOAT_EQ(xs[1].time(), -4.0);
}

TEST(Intersections, setTheObjectOnIntersection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_TRUE(&xs[0].object() == &s);
  ASSERT_TRUE(&xs[1].object() == &s);
}

TEST(Hit, callFunction) {
  Sphere s;
  std::vector<Intersection> intersections = {Intersection(0, s),
                                             Intersection(1, s)};
  hit(intersections);
}

TEST(Hit, getIntersectionAsHit) {
  Sphere s;
  std::vector<Intersection> intersections = {Intersection(0, s),
                                             Intersection(1, s)};
  Intersection i = hit(intersections);
}
