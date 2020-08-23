#include <gtest/gtest.h>
#include <utility/Float_compare.hpp>

TEST(Float_compare, takesTwoFloatingPointNumbers) { float_equals(1.0, 2.0); }

TEST(Float_compare, returnsBoolean) {
  const bool result = float_equals(0.0, 0.0);
}

TEST(Float_compare, numberIsEqualToItself) {
  const double number = 1.0;
  ASSERT_TRUE(float_equals(number, number));
}

TEST(Float_compare, differentNumbersNotEqual) {
  const double zero = 0.0;
  const double one = 1.0;
  ASSERT_FALSE(float_equals(zero, one));
}

TEST(Float_compare, nearNumbersAreEqual) {
  const double number1 = 1.000000;
  const double number2 = 1.000001;
  ASSERT_TRUE(float_equals(number1, number2));
}
