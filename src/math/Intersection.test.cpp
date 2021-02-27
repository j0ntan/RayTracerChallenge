#include <gtest/gtest.h>
#include <math/Intersection.hpp>
#include <math/Sphere.hpp>

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
