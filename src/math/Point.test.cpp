#include <gtest/gtest.h>

#include <math/Point.hpp>

TEST(PointConstructor, callConstructor) { Point p; }

TEST(PointAccessor, callAccessors) {
  Point p;
  double result_x = p.x();
  double result_y = p.y();
  double result_z = p.z();
}

TEST(PointConstructor, defaultValuesZeroed) {
  Point p;
  ASSERT_FLOAT_EQ(p.x(), 0.0);
  ASSERT_FLOAT_EQ(p.y(), 0.0);
  ASSERT_FLOAT_EQ(p.z(), 0.0);
}

TEST(PointConstructor, takeInitialValues) { Point p(1.0, 2.0, 3.0); }

TEST(PointConstructor, matchInitialValues) {
  Point p(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(p.x(), 1.0);
  ASSERT_FLOAT_EQ(p.y(), 2.0);
  ASSERT_FLOAT_EQ(p.z(), 3.0);
}

TEST(PointConstructor, copyConstruct) {
  Point p1(1.0, 2.0, 3.0), p2(p1);
  ASSERT_FLOAT_EQ(p1.x(), p2.x());
  ASSERT_FLOAT_EQ(p1.y(), p2.y());
  ASSERT_FLOAT_EQ(p1.z(), p2.z());
}

TEST(PointEqualityOperator, equalToSelf) {
  Point p;
  ASSERT_TRUE(p == p);
}

TEST(PointEqualityOperator, equalToCopy) {
  Point p1, p2(p1);
  ASSERT_TRUE(p1 == p2);
}

TEST(PointEqualityOperator, notEqualToDifferentPoint) {
  Point p1, p2(1.0, 2.0, 3.0);
  ASSERT_FALSE(p1 == p2);
}

TEST(PointEqualityOperator, equalToVeryNearPoint) {
  Point p1, p2(0.0, 0.0, 0.000001);
  ASSERT_TRUE(p1 == p2);
}

TEST(PointAccessor, changeCoordinates) {
  Point p;
  p.x() = 1.0;
  p.y() = 2.0;
  p.z() = 3.0;
}

TEST(PointAssignmentOperator, assignFromPoint) {
  Point p1, p2(1.0, 2.0, 3.0);
  ASSERT_NE(p1, p2);
  p1 = p2;
  ASSERT_EQ(p1, p2);
}
