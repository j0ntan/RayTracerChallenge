#include <gtest/gtest.h>
#include <math/Tuple.hpp>

TEST(Tuple, defaultConstruct) { Tuple<> t; }

TEST(Tuple, getSize) { constexpr std::size_t size = Tuple<>().size; }

TEST(Tuple, emptyTupleHasSizeZero) {
  constexpr std::size_t size = Tuple<>().size;
  ASSERT_EQ(size, 0);
}

TEST(Tuple, initializeWithNonZeroSize) { Tuple<3> t; }

TEST(Tuple, sizeMatchesInitializationParameter) {
  constexpr std::size_t size = Tuple<3>().size;
  ASSERT_EQ(size, 3);
}

TEST(Tuple, accessElements) { Tuple<3>().elements; }

TEST(Tuple, initializeWithList) { Tuple<3> t = {1, 2, 3}; }

TEST(Tuple, matchValuesInInitializationList) {
  Tuple<3> t = {1, 2, 3};
  ASSERT_FLOAT_EQ(t.elements[0], 1);
  ASSERT_FLOAT_EQ(t.elements[1], 2);
  ASSERT_FLOAT_EQ(t.elements[2], 3);
}

TEST(Tuple, makeUninitializedElementsDefaultToZero) {
  const Tuple<3> ct = {1.1};
  ASSERT_FLOAT_EQ(ct.elements[0], 1.1);
  ASSERT_FLOAT_EQ(ct.elements[1], 0);
  ASSERT_FLOAT_EQ(ct.elements[2], 0);
}

TEST(Tuple, initializeWithArray) {
  std::array<double, 3> values = {1, 2, 3};
  Tuple<3> t(values);
}

TEST(Tuple, matchValuesInInitializationArray) {
  std::array<double, 3> values = {1, 2, 3};
  Tuple<3> t(values);
  ASSERT_FLOAT_EQ(t.elements[0], 1);
  ASSERT_FLOAT_EQ(t.elements[1], 2);
  ASSERT_FLOAT_EQ(t.elements[2], 3);
}

TEST(Tuple, accessElementsOperator) {
  const Tuple<3> ct = {1, 2, 3};
  const double first = ct[0];
  const double second = ct[1];
  const double third = ct[2];
}

TEST(Tuple, matchAccessedElementsWithInitializationValues) {
  const Tuple<3> ct = {1.1, 2.2, 3.3};
  ASSERT_FLOAT_EQ(ct[0], 1.1);
  ASSERT_FLOAT_EQ(ct[1], 2.2);
  ASSERT_FLOAT_EQ(ct[2], 3.3);
}

TEST(Tuple, rewriteAccessedElement) {
  Tuple<3> t = {1, 2, 3};
  t[0] = 123.123;
  ASSERT_FLOAT_EQ(t[0], 123.123);
}

TEST(Tuple, compareForEquality) { Tuple<3>() == Tuple<3>(); }

TEST(Tuple, equalToSelf) {
  Tuple<> t;
  ASSERT_TRUE(t == t);
}

TEST(Tuple, equalToCopy) {
  Tuple<1> t1, t2(t1);
  ASSERT_TRUE(t1 == t2);
}

TEST(Tuple, notEqualToDifferentTuple) {
  ASSERT_FALSE(Tuple<1>{1} == Tuple<1>{2});
}

TEST(Tuple, equalToVerySimilarTuple) {
  ASSERT_TRUE(Tuple<1>{1.} == Tuple<1>{1.000001});
}

TEST(Tuple, addTwoTuples) { Tuple<3>() + Tuple<3>(); }

TEST(Tuple, getTuplefromTupleAddition) { Tuple<3> t = Tuple<3>() + Tuple<3>(); }

TEST(Tuple, addingTuplesAddsElements) {
  Tuple<2> t1 = {1.1, 2.2};
  Tuple<2> t2 = {3.3, 4.4};
  ASSERT_EQ((Tuple<2>{4.4, 6.6}), t1 + t2);
}

TEST(Tuple, subtractTwoTuples) { Tuple<3>() - Tuple<3>(); }

TEST(Tuple, getTuplefromTupleSubtraction) {
  Tuple<3> t = Tuple<3>() - Tuple<3>();
}

TEST(Tuple, subtractingTuplesSubtractsElements) {
  Tuple<2> t1 = {1.1, 2.2};
  Tuple<2> t2 = {3.3, 4.4};
  ASSERT_EQ((Tuple<2>{2.2, 2.2}), t2 - t1);
}

TEST(Tuple, multiplyTwoTuples) { Tuple<3>() * Tuple<3>(); }

TEST(Tuple, getTuplefromTupleMultiplication) {
  Tuple<3> t = Tuple<3>() * Tuple<3>();
}

TEST(Tuple, multiplyingTuplesMultipliesElements) {
  Tuple<2> t1 = {1.1, 2.2};
  Tuple<2> t2 = {3.3, 4.4};
  ASSERT_EQ((Tuple<2>{3.63, 9.68}), t2 * t1);
}

TEST(Tuple, takeInnerProduct) {
  const double result = inner_product(Tuple<3>(), Tuple<3>());
}

TEST(Tuple, calculateInnerProductValue) {
  const Tuple<2> t1 = {1.1, 2.2};
  const Tuple<2> t2 = {3.3, 4.4};
  ASSERT_FLOAT_EQ(inner_product(t1, t2), 13.31);
}

TEST(Tuple, multiplyByScalar) { Tuple<>() * 1.; }

TEST(Tuple, getTupleFromScalarMultiplication) { Tuple<3> t = Tuple<3>() * 1.; }

TEST(Tuple, calculateScalarMultiplication) {
  ASSERT_EQ((Tuple<3>{1, 2, 3} * 2.), (Tuple<3>{2, 4, 6}));
}

TEST(Tuple, multiplyScalarByTuple) {
  Tuple<3> t = {1, 2, 3};
  ASSERT_EQ(2 * t, t * 2);
}

TEST(Tuple, divideByScalar) { Tuple<>() / 1.; }

TEST(Tuple, getTupleFromScalarDivision) { Tuple<3> t = Tuple<3>() / 1.; }

TEST(Tuple, calculateScalarDivision) {
  ASSERT_EQ((Tuple<3>{12, 34, 56} / 2.), (Tuple<3>{6, 17, 28}));
}

TEST(Tuple, applyNegation) { -Tuple<>(); }

TEST(Tuple, negateGivesAdditiveInverseOfElements) {
  ASSERT_EQ((-Tuple<3>{1, 2, 3}), (Tuple<3>{-1, -2, -3}));
}
