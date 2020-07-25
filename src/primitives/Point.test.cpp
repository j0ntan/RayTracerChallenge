#include <gtest/gtest.h>
#include <primitives/Point.hpp>

TEST(Point, defaultConstruct) { Point p; }

TEST(Point, accessThreeSpatialComponents) {
  Point p;
  p.x;
  p.y;
  p.z;
}

TEST(Point, componentsDefaultedToZero) {
  Point p;
  ASSERT_FLOAT_EQ(p.x, 0.0);
  ASSERT_FLOAT_EQ(p.y, 0.0);
  ASSERT_FLOAT_EQ(p.z, 0.0);
}

TEST(Point, initialValueConstructed) { Point p(1.0, 2.0, 3.0); }

TEST(Point, componentsMatchInitializationInputs) {
  Point p(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(p.x, 1.0);
  ASSERT_FLOAT_EQ(p.y, 2.0);
  ASSERT_FLOAT_EQ(p.z, 3.0);
}
