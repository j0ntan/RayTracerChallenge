#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include <scene/Intersection.hpp>
#include <scene/Sphere.hpp>

TEST(IntersectionConstructor, initializeWithSphere) {
  Sphere sphere;
  Intersection intersection(0, sphere);
}

TEST(IntersectionTime, accessTime) {
  Sphere sphere;
  Intersection intersection(0, sphere);
  double time = intersection.time();
}

TEST(IntersectionTime, matchTimeValue) {
  const double TIME = 1.0;
  Sphere sphere;
  Intersection intersection(TIME, sphere);

  ASSERT_EQ(intersection.time(), TIME);
}

TEST(IntersectionObject, accessSphere) {
  Sphere sphere;
  Intersection intersection(1, sphere);
  const Sphere &object = intersection.object();
}

TEST(IntersectionObject, matchSphereObject) {
  Sphere sphere;
  Intersection intersection(1, sphere);

  ASSERT_EQ(&sphere, &intersection.object());
}

TEST(IntersectionEqualityOperator, isEqualToSame) {
  const double TIME_VALUE = 1.0;
  Sphere sphere;
  Intersection intersection1(TIME_VALUE, sphere),
      intersection2(TIME_VALUE, sphere);
  ASSERT_EQ(intersection1, intersection2);
}

TEST(IntersectionEqualityOperator, isNotEqualForDifferingTime) {
  const double TIME1 = 1.0, TIME2 = 2.0;
  Sphere sphere;
  Intersection intersection1(TIME1, sphere), intersection2(TIME2, sphere);
  ASSERT_NE(intersection1, intersection2);
}

TEST(IntersectionEqualityOperator, isNotEqualForDifferingSpheres) {
  const double TIME_VALUE = 1.0;
  Sphere sphere1, sphere2;
  Intersection intersection1(TIME_VALUE, sphere1),
      intersection2(TIME_VALUE, sphere2);
  ASSERT_NE(intersection1, intersection2);
}

TEST(IntersectionLessThanOperator, isComparable) {
  Sphere sphere;
  Intersection intersection1(1, sphere), intersection2(2, sphere);
  bool result = intersection1 < intersection2;
}

TEST(IntersectionLessThanOperator, compareCorrectly) {
  double time1 = 1, time2 = 2;
  Sphere sphere;
  Intersection intersection1(time1, sphere), intersection2(time2, sphere);
  ASSERT_TRUE(intersection1 < intersection2);
  ASSERT_FALSE(intersection2 < intersection1);
}

TEST(IntersectionSortable, isSortable) {
  double time1 = 1, time2 = 2;
  Sphere sphere;
  Intersection intersection1(time1, sphere), intersection2(time2, sphere);
  std::vector<Intersection> intersections;
  std::sort(intersections.begin(), intersections.end());
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
