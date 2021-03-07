#include <algorithm>
#include <gtest/gtest.h>
#include <scene/Intersection.hpp>
#include <scene/Sphere.hpp>
#include <vector>

TEST(Intersection, constructWithTimeValueAndSphere) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
}

TEST(Intersection, accessTimeValue) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
  const double t = i.time();
}

TEST(Intersection, matchTimeValue) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
  ASSERT_EQ(i.time(), time_value);
}

TEST(Intersection, accessSphere) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
  Sphere copy(i.object());
}

TEST(Intersection, matchSphereObject) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
  ASSERT_TRUE(&s == &i.object());
}

TEST(Intersection, equalToSameIntersection) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i1(time_value, s), i2(time_value, s);
  ASSERT_EQ(i1, i2);
}

TEST(Intersection, notEqualForDifferingTime) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i1(time_value, s), i2(time_value + 1, s);
  ASSERT_NE(i1, i2);
}

TEST(Intersection, notEqualForDifferingSpheres) {
  const double time_value = 1.0;
  Sphere s1, s2;
  Intersection i1(time_value, s1), i2(time_value, s2);
  ASSERT_NE(i1, i2);
}

TEST(Intersection, canBeAssigned) {
  Sphere s;
  Intersection i1(1, s), i2(2, s);
  i2 = i1;
}

TEST(Intersection, isEqualAfterAssignment) {
  Sphere s;
  Intersection i1(1, s), i2(2, s);
  i2 = i1;
  ASSERT_EQ(i1, i2);
}

TEST(Intersection, isComparible) {
  Sphere s;
  Intersection i1(1, s), i2(2, s);
  i1 < i2;
}

TEST(Intersection, correctComparison) {
  Sphere s;
  Intersection i1(1, s), i2(2, s);
  ASSERT_TRUE(i1 < i2);
  ASSERT_FALSE(i2 < i1);
}

TEST(Intersection, isSortable) {
  Sphere s;
  Intersection i1(1, s);
  Intersection i2(2, s);
  Intersection i3(3, s);
  std::vector<Intersection> v = {i1, i2, i3};
  std::sort(v.begin(), v.end());
}
