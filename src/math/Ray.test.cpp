#include <gtest/gtest.h>
#include <math/Ray.hpp>

TEST(Ray, constructWithOriginAndDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
}

TEST(Ray, accessOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  r.origin;
}

TEST(Ray, matchGivenOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  ASSERT_EQ(r.origin, origin);
}
