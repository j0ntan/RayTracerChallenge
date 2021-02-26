#include <gtest/gtest.h>
#include <math/Intersection.hpp>
#include <math/Sphere.hpp>

TEST(Intersection, constructWithTimeValueAndSphere) {
  const double time_value = 1.0;
  Sphere s;
  Intersection i(time_value, s);
}
