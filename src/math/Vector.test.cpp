#include <cmath>
#include <gtest/gtest.h>

#include <math/Vector.hpp>

TEST(VectorConstructor, defaultConstruct) { Vector v; }

TEST(VectorAccessor, callAccessors) {
  Vector v;
  double result_x = v.x();
  double result_y = v.y();
  double result_z = v.z();
}

TEST(VectorConstructor, defaultValuesZeroed) {
  Vector v;
  ASSERT_FLOAT_EQ(v.x(), 0.0);
  ASSERT_FLOAT_EQ(v.y(), 0.0);
  ASSERT_FLOAT_EQ(v.z(), 0.0);
}

TEST(VectorConstructor, takeInitialValues) { Vector v(1.0, 2.0, 3.0); }

TEST(VectorConstructor, matchInitialValues) {
  Vector v(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(v.x(), 1.0);
  ASSERT_FLOAT_EQ(v.y(), 2.0);
  ASSERT_FLOAT_EQ(v.z(), 3.0);
}

TEST(VectorConstructor, copyConstruct) {
  Vector v1(1.0, 2.0, 3.0), v2(v1);
  ASSERT_EQ(v1, v2);
}

TEST(VectorEqualityOperator, equalToSelf) {
  Vector v;
  ASSERT_TRUE(v == v);
}

TEST(VectorEqualityOperator, equalToCopy) {
  Vector v1, v2(v1);
  ASSERT_TRUE(v1 == v2);
}

TEST(VectorEqualityOperator, notEqualToDifferentVector) {
  Vector v1, v2(1.0, 2.0, 3.0);
  ASSERT_FALSE(v1 == v2);
}

TEST(VectorEqualityOperator, equalToVeryNearVector) {
  Vector v1, v2(0.0, 0.0, 0.000001);
  ASSERT_TRUE(v1 == v2);
}

TEST(VectorAccessor, changeCoordinates) {
  Vector v;
  v.x() = 1.0;
  v.y() = 2.0;
  v.z() = 3.0;
}

TEST(VectorAssignmentOperator, assignFromVector) {
  Vector v1, v2(1.0, 2.0, 3.0);
  ASSERT_NE(v1, v2);
  v1 = v2;
  ASSERT_EQ(v1, v2);
}

TEST(VectorAdditionOperator, addPointToVector) {
  Vector v(1.0, 2.0, 3.0);
  Point p(4.0, 5.0, 6.0), expected(5.0, 7.0, 9.0);
  ASSERT_EQ(v + p, expected);
}

TEST(VectorAdditionOperator, addVectorToPoint) {
  Vector v(1.0, 2.0, 3.0);
  Point p(4.0, 5.0, 6.0), expected(5.0, 7.0, 9.0);
  ASSERT_EQ(p + v, expected);
}

TEST(VectorAdditionOperator, addTwoVectors) {
  Vector v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0), expected(5.0, 7.0, 9.0);
  ASSERT_EQ(v1 + v2, expected);
}

TEST(VectorSubtractionOperator, subtractTwoPoints) {
  Point p1(4.0, 5.0, 6.0), p2(1.0, 2.0, 3.0);
  Vector expected1(3.0, 3.0, 3.0), expected2(-3.0, -3.0, -3.0);
  ASSERT_EQ(p1 - p2, expected1);
  ASSERT_EQ(p2 - p1, expected2);
}

TEST(VectorSubtractionOperator, subtractVectorFromPoint) {
  Point p = Point(4.0, 5.0, 6.0), expected(3.0, 3.0, 3.0);
  Vector v(1.0, 2.0, 3.0);
  ASSERT_EQ(p - v, expected);
}

TEST(VectorSubtractionOperator, subtractTwoVectors) {
  Vector v1(4.0, 5.0, 6.0), v2(1.0, 2.0, 3.0);
  Vector expected1(3.0, 3.0, 3.0), expected2(-3.0, -3.0, -3.0);
  ASSERT_EQ(v1 - v2, expected1);
  ASSERT_EQ(v2 - v1, expected2);
}

TEST(VectorNegationOperator, negateVector) {
  Vector v(0.0, 1.0, 2.0), expected(0.0, -1.0, -2.0);
  ASSERT_EQ(-v, expected);
}

TEST(VectorMultiplicationOperator, multiplyByScalar) {
  Vector v(1.0, 2.0, 3.0);
  double scalar1 = 0.5, scalar2 = -2.0;
  Vector expected1(0.5, 1.0, 1.5), expected2(-2.0, -4.0, -6.0);
  ASSERT_EQ(v * scalar1, expected1);
  ASSERT_EQ(v * scalar2, expected2);
}

TEST(VectorMultiplicationOperator, multiplyScalarByVector) {
  double scalar1 = 0.5, scalar2 = -2.0;
  Vector v(1.0, 2.0, 3.0), expected1(0.5, 1.0, 1.5),
      expected2(-2.0, -4.0, -6.0);
  ASSERT_EQ(scalar1 * v, expected1);
  ASSERT_EQ(scalar2 * v, expected2);
}

TEST(VectorDivisionOperator, divideByScalar) {
  double scalar = 2.0;
  Vector v(2.0, 4.0, 6.0), expected(1.0, 2.0, 3.0);
  ASSERT_EQ(v / scalar, expected);
}

TEST(VectorMagnitude, getMagnitude) {
  Vector v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1), v4(1, 2, 3);
  double expected1 = 1.0, expected2 = std::sqrt(14);
  ASSERT_FLOAT_EQ(v1.magnitude(), expected1);
  ASSERT_FLOAT_EQ(v2.magnitude(), expected1);
  ASSERT_FLOAT_EQ(v3.magnitude(), expected1);
  ASSERT_FLOAT_EQ(v4.magnitude(), expected2);
  ASSERT_FLOAT_EQ((-v4).magnitude(), expected2);
}

TEST(VectorNormalization, normalize) {
  Vector v(1, 2, 3),
      normal = v.normalize(),
      expected(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14));
  ASSERT_EQ(normal, expected);
}

TEST(VectorNormalization, normalIsUnitVector) {
  Vector v(1, 2, 3), normal = v.normalize();
  ASSERT_FLOAT_EQ(normal.magnitude(), 1.0);
}

TEST(VectorDotProduct, takeDotProduct) {
  Vector v1(1, 2, 3), v2(2, 3, 4);
  double expected = 20.0;
  ASSERT_FLOAT_EQ(dot(v1, v2), expected);
}

TEST(VectorCrossProduct, takeCrossProduct) {
  Vector v1(1, 2, 3), v2(2, 3, 4);
  Vector expected1(-1, 2, -1), expected2(1, -2, 1);
  ASSERT_EQ(cross(v1, v2), expected1);
  ASSERT_EQ(cross(v2, v1), expected2);
}

TEST(VectorReflection, reflectTwoVectors) {
  Vector incident(1, 0, 0), normal(0, 1, 0);
  Vector reflected = reflect(incident, normal);
}

TEST(VectorReflection, vectorAt45Degrees) {
  Vector incident(1, -1, 0), normal(0, 1, 0);
  Vector expected(1, 1, 0);
  ASSERT_EQ(reflect(incident, normal), expected);
}

TEST(VectorReflection, slantedSurface) {
  Vector incident(0, -1, 0), normal(sqrt(2) / 2, sqrt(2) / 2, 0);
  Vector expected(1, 0, 0);
  ASSERT_EQ(reflect(incident, normal), expected);
}
