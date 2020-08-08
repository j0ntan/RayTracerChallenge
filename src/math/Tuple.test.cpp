#include <gtest/gtest.h>
#include <math/Tuple.hpp>

TEST(Tuple, defaultConstruct) { Tuple<> t; }

TEST(Tuple, getSize) { std::size_t size = Tuple<>().size; }

TEST(Tuple, emptyTupleHasSizeZero) { ASSERT_EQ(Tuple<>().size, 0); }

TEST(Tuple, initializeWithNonZeroSize) { Tuple<3> t; }

TEST(Tuple, sizeMatchesInitializationParameter) {
  ASSERT_EQ(Tuple<3>().size, 3);
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
