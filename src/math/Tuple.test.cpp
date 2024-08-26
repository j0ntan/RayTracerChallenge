#include <gtest/gtest.h>

#include <math/Tuple.hpp>

TEST(TupleConstructor, callConstructor) { Tuple<> t; }

TEST(TupleConstructor, initializeWithNonZeroSize) { Tuple<3> t; }

TEST(TupleElements, accessMember) {
  Tuple<3> t;
  std::array<double, 3> &elements = t.elements;
}

TEST(TupleListConstructor, initializeWithList) { Tuple<3> t = {1, 2, 3}; }

TEST(TupleListConstructor, matchValuesInList) {
  Tuple<3> t = {1, 2, 3};
  ASSERT_FLOAT_EQ(t.elements[0], 1);
  ASSERT_FLOAT_EQ(t.elements[1], 2);
  ASSERT_FLOAT_EQ(t.elements[2], 3);
}

TEST(TupleListConstructor, checkUninitializedElementsDefaultToZero) {
  const Tuple<3> ct = {1.1};
  ASSERT_FLOAT_EQ(ct.elements[0], 1.1);
  ASSERT_FLOAT_EQ(ct.elements[1], 0);
  ASSERT_FLOAT_EQ(ct.elements[2], 0);
}

TEST(TupleArrayConstructor, initializeWithArray) {
  std::array<double, 3> values = {1, 2, 3};
  Tuple<3> t(values);
}

TEST(TupleArrayConstructor, matchValuesInInitializationArray) {
  std::array<double, 3> values = {1, 2, 3};
  Tuple<3> t(values);
  ASSERT_FLOAT_EQ(t.elements[0], 1);
  ASSERT_FLOAT_EQ(t.elements[1], 2);
  ASSERT_FLOAT_EQ(t.elements[2], 3);
}

TEST(TupleAccessOperator, callOperator) {
  Tuple<1> t;
  double value = t[0];
}

TEST(TupleAccessOperator, matchAccessedWithInitialization) {
  const Tuple<3> ct = {1.1, 2.2, 3.3};
  ASSERT_FLOAT_EQ(ct[0], 1.1);
  ASSERT_FLOAT_EQ(ct[1], 2.2);
  ASSERT_FLOAT_EQ(ct[2], 3.3);
}

TEST(TupleAccessOperator, rewriteAccessedElement) {
  Tuple<3> t = {1, 2, 3};
  t[0] = 123.123;
  ASSERT_FLOAT_EQ(t[0], 123.123);
}

TEST(TupleEqualityOperator, callOperator) {
  Tuple<> t;
  bool result = t == t;
}

TEST(TupleEqualityOperator, equalToSelf) {
  Tuple<> t;
  ASSERT_TRUE(t == t);
}

TEST(TupleEqualityOperator, notEqualToDifferentTuple) {
  Tuple<1> t1{1}, t2{2};
  ASSERT_FALSE(t1 == t2);
}

TEST(TupleEqualityOperator, equalToVerySimilarTuple) {
  Tuple<1> t1{1.0}, t2{1.000001};
  ASSERT_TRUE(t1 == t2);
}

TEST(TupleInequalityOperator, callOperator) {
  Tuple<1> a;
  a != a;
}

TEST(TupleInequalityOperator, checkInverseOfEqualityTests) {
  Tuple<2> t1{123, 456}, t2{0.1, 0.2}, t3{0.100001, 0.2000001};
  ASSERT_FALSE(t1 != t1); // compare with self
  ASSERT_TRUE(t1 != t2);  // compare with other & different
  ASSERT_FALSE(t2 != t3); // compare with very similar, effectively same
}

TEST(TupleAdditionOperator, callOperator) {
  Tuple<1> t;
  Tuple<1> result = t + t;
}

TEST(TupleAdditionOperator, addElementValues) {
  Tuple<2> t1 = {1.1, 2.2}, t2 = {3.3, 4.4}, expected = {4.4, 6.6};
  ASSERT_EQ(t1 + t2, expected);
}

TEST(TupleSubtractionOperator, callOperator) {
  Tuple<1> t;
  Tuple<1> result = t - t;
}

TEST(TupleSubtractionOperator, subtractElementValues) {
  Tuple<2> t1{1.1, 2.2}, t2{3.3, 4.4};
  Tuple<2> expected1{2.2, 2.2}, expected2{-2.2, -2.2};
  ASSERT_EQ(t2 - t1, expected1);
  ASSERT_EQ(t1 - t2, expected2);
}

TEST(TupleMultiplicationOperator, callOperator) {
  Tuple<3> t;
  Tuple<3> result = t * t;
}

TEST(TupleMultiplicationOperator, multiplyElementValues) {
  Tuple<2> t1{1.1, 2.2}, t2{3.3, 4.4}, expected{3.63, 9.68};
  ASSERT_EQ(t2 * t1, expected);
}

TEST(TupleInnerProduct, takeInnerProduct) {
  Tuple<1> t;
  const double result = inner_product(t, t);
}

TEST(TupleInnerProduct, checkInnerProductCalculation) {
  const Tuple<2> t1 = {1.1, 2.2}, t2 = {3.3, 4.4};
  double expected = 13.31;
  ASSERT_FLOAT_EQ(inner_product(t1, t2), expected);
}

TEST(TupleScalarMultiplication, callOperator) {
  Tuple<1> t;
  Tuple<1> result = t * 1.0;
}

TEST(TupleScalarMultiplication, calculateScalarMultiplication) {
  Tuple<3> t{1, 2, 3}, expected{2, 4, 6};
  ASSERT_EQ(t * 2.0, expected);
}

TEST(TupleScalarMultiplication, checkCommutativeProperty) {
  Tuple<3> t{1, 2, 3}, expected{2, 4, 6};
  ASSERT_EQ(2.0 * t, expected);
}

TEST(TupleScalarDivision, callOperator) {
  Tuple<1> t;
  Tuple<1> result = t / 1.0;
}

TEST(TupleScalarDivision, checkDivisionResults) {
  Tuple<3> t{12, 34, 56}, expected{6, 17, 28};
  double divisor = 2.0;
  ASSERT_EQ(t / divisor, expected);
}

TEST(TupleNegationOperator, callOperator) {
  Tuple<1> t;
  Tuple<1> result = -t;
}

TEST(TupleNegationOperator, checkNegatedElements) {
  Tuple<3> t{1, 2, 3}, expected{-1, -2, -3};
  ASSERT_EQ(-t, expected);
}
