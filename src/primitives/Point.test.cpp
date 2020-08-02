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

TEST(Point, copyConstruct) {
  Point p1(1.0, 2.0, 3.0);
  Point p2(p1);
}

TEST(Point, copiedComponentsMatch) {
  Point p1(1.0, 2.0, 3.0);
  Point p2(p1);
  ASSERT_FLOAT_EQ(p1.x, p2.x);
  ASSERT_FLOAT_EQ(p1.y, p2.y);
  ASSERT_FLOAT_EQ(p1.z, p2.z);
}

TEST(Point, callPointComparator) {
  Point p1, p2;
  p1 == p2;
}

TEST(Point, equalToSelf) {
  Point p;
  ASSERT_TRUE(p == p);
}

TEST(Point, equalToCopy) {
  Point p1, p2(p1);
  ASSERT_TRUE(p1 == p2);
}

TEST(Point, notEqualToDifferentPoint) {
  Point p1, p2(1.0, 2.0, 3.0);
  ASSERT_FALSE(p1 == p2);
}

TEST(Point, equalToVeryNearPoint) {
  Point p1, p2(0.0, 0.0, 0.000001);
  ASSERT_TRUE(p1 == p2);
}

TEST(Point, changeCoordinates) {
  Point p;
  p.x = 1.0;
  p.y = 2.0;
  p.z = 3.0;
}

TEST(Point, assignFromPoint) {
  Point p1, p2(1.0, 2.0, 3.0);
  p1 = p2;
  ASSERT_EQ(p1, p2);
}
