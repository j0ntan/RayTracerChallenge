#include <gtest/gtest.h>
#include <math/Sphere.hpp>

TEST(Sphere, defaultConstruct) { Sphere s; }

TEST(Sphere, constructWithRadiusAndOrigin) { Sphere s(1.0, Point()); }

TEST(Sphere, accessRadius) {
  const Sphere s;
  s.radius();
}

TEST(Sphere, defaultUnityRadius) {
  Sphere s;
  ASSERT_EQ(s.radius(), 1.0);
}

TEST(Sphere, radiusMatchesGivenValue) {
  const double RADIUS = 1.23;
  Sphere s(RADIUS, Point());
  ASSERT_EQ(s.radius(), RADIUS);
}

TEST(Sphere, accessOrigin) {
  const Sphere s;
  s.origin();
}

TEST(Sphere, defaultZeroOrigin) {
  Sphere s;
  ASSERT_EQ(s.origin(), Point(0, 0, 0));
}

TEST(Sphere, originMatchesGivenValue) {
  const Point ORIGIN(1, 2, 3);
  Sphere s(0, ORIGIN);
  ASSERT_EQ(s.origin(), ORIGIN);
}