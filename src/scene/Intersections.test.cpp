#include <gtest/gtest.h>
#include <scene/Intersections.hpp>
#include <scene/Transformations.hpp>

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
  std::optional<Intersection> i = hit(intersections);
}

TEST(Hit, allPositiveTimeValues) {
  Sphere s;
  Intersection i1(1, s);
  Intersection i2(2, s);
  std::vector<Intersection> xs = {i2, i1};
  auto i = hit(xs);
  ASSERT_EQ(i, i1);
}

TEST(Hit, mixedTimeValues) {
  Sphere s;
  Intersection i1(-1, s);
  Intersection i2(1, s);
  std::vector<Intersection> xs = {i2, i1};
  auto i = hit(xs);
  ASSERT_EQ(i, i2);
}

TEST(Hit, allNegativeTimeValues) {
  Sphere s;
  Intersection i1(-2, s);
  Intersection i2(-1, s);
  std::vector<Intersection> xs = {i2, i1};
  auto i = hit(xs);
  ASSERT_FALSE(i.has_value());
}

TEST(Hit, getsLowestNonNegativeIntersection) {
  Sphere s;
  Intersection i1(5, s);
  Intersection i2(7, s);
  Intersection i3(-3, s);
  Intersection i4(2, s);
  std::vector<Intersection> xs = {i1, i2, i3, i4};
  auto i = hit(xs);
  ASSERT_EQ(i, i4);
}

TEST(ApplyRayTransformation, scaledSphereAndRayIntersection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transformation(scale(2, 2, 2));
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 2);
  ASSERT_EQ(xs[0].time(), 3);
  ASSERT_EQ(xs[1].time(), 7);
}

TEST(ApplyRayTransformation, translatedSphereAndRayIntersection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transformation(translate(5, 0, 0));
  auto xs = intersect(s, r);
  ASSERT_EQ(xs.size(), 0);
}
