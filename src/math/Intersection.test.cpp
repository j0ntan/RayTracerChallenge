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
  const double t = i.t;
}

TEST(Intersection, matchTimeValue) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
  ASSERT_EQ(i.t, time_value);
}
