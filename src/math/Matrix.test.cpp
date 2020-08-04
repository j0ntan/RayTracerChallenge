#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(Matrix, defaultConstruct) { Matrix<> m; }

TEST(Matrix, defaultSizeIsTwo) { ASSERT_EQ(Matrix<>().size, 2); }

TEST(Matrix, constructWithGivenSize) {
  Matrix<3> m;
  ASSERT_EQ(m.size, 3);
}

TEST(Matrix, accessValues) { Matrix<>().values[0]; }

TEST(Matrix, writeValuesUsingIndexOperator) {
  Matrix<> m;
  m(0, 0) = 1;
  ASSERT_FLOAT_EQ(m(0, 0), 1);
  m(1, 0) = 2;
  ASSERT_FLOAT_EQ(m(1, 0), 2);
}

TEST(Matrix, allElementsDefaultToZero) {
  Matrix<3> m;
  for (std::size_t row; row < 3; ++row)
    for (std::size_t col; col < 3; ++col)
      ASSERT_FLOAT_EQ(m(row, col), 0);
}
