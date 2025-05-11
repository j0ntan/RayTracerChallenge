#include <Float_compare.hpp>
#include <gtest/gtest.h>

TEST(Float_compareEquality, numberIsEqualToItself)
{
    const double NUMBER = 1.0;
    ASSERT_TRUE(float_equals(NUMBER, NUMBER));
}

TEST(Float_compareEquality, differentNumbersNotEqual)
{
    const double ZERO = 0.0;
    const double ONE = 1.0;
    ASSERT_FALSE(float_equals(ZERO, ONE));
}

TEST(Float_compareEquality, nearNumbersAreEqual)
{
    const double NUMBER1 = 1.000000;
    const double NUMBER2 = 1.000001;
    ASSERT_TRUE(float_equals(NUMBER1, NUMBER2));
}
