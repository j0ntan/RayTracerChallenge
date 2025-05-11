#include <stdexcept>
#include <Math/Tuple.hpp>
#include <Math/Point.hpp>
#include <Math/Vector.hpp>
#include <gtest/gtest.h>

TEST(TupleIterator, accessByConstRef)
{
    const Tuple TUPLE{4, 3, 2, 1};

    const double *first = TUPLE.cbegin();
    const double *last = TUPLE.cend();

    ASSERT_EQ(first, &TUPLE.x());
    ASSERT_EQ(last, &TUPLE.w() + 1);
}

TEST(TupleIterator, modifyUsingIterator)
{
    Tuple tuple{1, 2, 3, 4};
    for (auto &val : tuple)
    {
        val = 1.234;
    }
    ASSERT_FLOAT_EQ(tuple.x(), 1.234);
    ASSERT_FLOAT_EQ(tuple.y(), 1.234);
    ASSERT_FLOAT_EQ(tuple.z(), 1.234);
    ASSERT_FLOAT_EQ(tuple.w(), 1.234);
}

/*
Scenario: A tuple with w=1.0 is a point
    Given a <- tuple(4.3, -4.2, 3.1, 1.0)
    Then a.x = 4.3
        And a.y = -4.2
        And a.z = 3.1
        And a.w = 1.0
        And a is a point
        And a is not a vector
*/
TEST(TupleIsPoint, confirmPointType)
{
    auto a = Tuple(4.3, -4.2, 3.1, 1);

    ASSERT_FLOAT_EQ(a.x(), 4.3);
    ASSERT_FLOAT_EQ(a.y(), -4.2);
    ASSERT_FLOAT_EQ(a.z(), 3.1);
    ASSERT_FLOAT_EQ(a.w(), 1.0);
    ASSERT_NO_THROW(Point is_a_point{a});
    ASSERT_THROW(Vector is_not_a_vector{a}, std::invalid_argument);
}

/*
Scenario: A tuple with w=0 is a vector
    Given a <- tuple(4.3, -4.2, 3.1, 0.0)
    Then a.x = 4.3
        And a.y = -4.2
        And a.z = 3.1
        And a.w = 0.0
        And a is not a point
        And a is a vector
*/
TEST(TupleIsVector, confirmVectorType)
{
    auto a = Tuple{4.3, -4.2, 3.1, 0.0};

    ASSERT_FLOAT_EQ(a.x(), 4.3);
    ASSERT_FLOAT_EQ(a.y(), -4.2);
    ASSERT_FLOAT_EQ(a.z(), 3.1);
    ASSERT_FLOAT_EQ(a.w(), 0.0);
    ASSERT_THROW(Point is_not_a_point{a}, std::invalid_argument);
    ASSERT_NO_THROW(Vector is_a_vector{a});
}

TEST(TupleEquality, isEqualToItself)
{
    Tuple a{1, 2, 3, 4};

    ASSERT_EQ(a, a);
}

TEST(TupleEquality, isEqualToSimilar)
{
    Tuple a{1, 2, 3, 4}, b{1.00001, 2.00002, 3.0003, 4.00004};

    ASSERT_EQ(a, a);
}

/*
Scenario: Adding two tuples
    Given a1 <- tuple(3, -2, 5, 1)
        And a2 <- tuple(-2, 3, 1, 0)
    Then a1 + a2 = tuple(1, 1, 6, 1)
*/
TEST(TupleAddition, matchSummedComponents)
{
    auto a1 = Tuple{3, -2, 5, 1};
    auto a2 = Tuple{-2, 3, 1, 0};

    ASSERT_EQ(a1 + a2, Tuple(1, 1, 6, 1));
}

TEST(TupleSubtraction, matchSubtractedComponents)
{
    auto a1 = Tuple{3, -2, 5, 1};
    auto a2 = Tuple{-2, 3, 1, 0};

    ASSERT_EQ(a1 - a2, Tuple(5, -5, 4, 1));
}

/*
Scenario: Negating a tuple
    Given a <- tuple(1, -2, 3, -4)
    Then -a = tuple(-1, 2, -3,  4)
*/
TEST(TupleNegateOp, matchNegatedComponents)
{
    auto a = Tuple{1, -2, 3, -4};

    ASSERT_EQ(-a, Tuple(-1, 2, -3, 4));
}

/*
Scenario: Multiplying a tuple by a scalar
    Given a <- tuple(1, -2, 3, -4)
    Then a * 3.5 = tuple(3.5, -7, 10.5, -14)
*/
TEST(TupleScalarMultiplicationOp, matchScaledComponents)
{
    auto a = Tuple{1, -2, 3, -4};

    ASSERT_EQ(a * 3.5, Tuple(3.5, -7, 10.5, -14));
}

/*
Scenario: Multiplying a tuple by a fraction
    Given a <- tuple(1, -2, 3, -4)
    Then a * 0.5 = tuple(0.5, -1, 1.5, -2)
*/
TEST(TupleScalarMultiplicationOp, multiplyFractional)
{
    auto a = Tuple{1, -2, 3, -4};

    ASSERT_EQ(a * 0.5, Tuple(0.5, -1, 1.5, -2));
}

/*
Scenario: Dividing a tuple by a scalar
    Given a <- tuple(1, -2, 3, -4)
    Then a / 2 = tuple(0.5, -1, 1.5, -2)
*/
TEST(TupleScalarDivisionOp, matchDividedComponents)
{
    auto a = Tuple{1, -2, 3, -4};

    ASSERT_EQ(a / 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleDotProduct, calculateDotProduct)
{
    Tuple t1{1, 2, 3, 4}, t2{5, 6, 7, 8};

    ASSERT_FLOAT_EQ(dot(t1, t2), 70);
}

TEST(TupleCtor, initializeWithArray)
{
    std::array<double, 4> values{1, 2, 3, 4};
    Tuple tuple(values);
}
