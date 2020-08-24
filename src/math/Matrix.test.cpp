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

TEST(Matrix, constructWithSimpleList) {
  Matrix<2> m = {1, 2, 3, 4};
  ASSERT_FLOAT_EQ(m(0, 0), 1);
  ASSERT_FLOAT_EQ(m(0, 1), 2);
  ASSERT_FLOAT_EQ(m(1, 0), 3);
  ASSERT_FLOAT_EQ(m(1, 1), 4);
}

TEST(Matrix, useSimpleListWithNonMatchingSize) {
  Matrix<2> m1 = {1};
  ASSERT_FLOAT_EQ(m1(0, 0), 1);
  ASSERT_FLOAT_EQ(m1(0, 1), 0);
  ASSERT_FLOAT_EQ(m1(1, 0), 0);
  ASSERT_FLOAT_EQ(m1(1, 1), 0);

  Matrix<2> m2 = {1, 2, 3, 4, 5, 6};
  ASSERT_FLOAT_EQ(m2(0, 0), 1);
  ASSERT_FLOAT_EQ(m2(0, 1), 2);
  ASSERT_FLOAT_EQ(m2(1, 0), 3);
  ASSERT_FLOAT_EQ(m2(1, 1), 4);
}

TEST(Matrix, constructWithNestedLists) {
  Matrix<2> m = {{1, 2}, {3, 4}};
  ASSERT_FLOAT_EQ(m(0, 0), 1);
  ASSERT_FLOAT_EQ(m(0, 1), 2);
  ASSERT_FLOAT_EQ(m(1, 0), 3);
  ASSERT_FLOAT_EQ(m(1, 1), 4);
}

TEST(Matrix, useNestedListWithRowsOfNonMatchingSize) {
  Matrix<2> m1 = {{1}, {2, 3, 4}};
  ASSERT_FLOAT_EQ(m1(0, 0), 1);
  ASSERT_FLOAT_EQ(m1(0, 1), 0);
  ASSERT_FLOAT_EQ(m1(1, 0), 2);
  ASSERT_FLOAT_EQ(m1(1, 1), 3);
}

TEST(Matrix, useNestedListWithNonMatchingRows) {
  Matrix<2> m1 = {{1, 2}};
  ASSERT_FLOAT_EQ(m1(0, 0), 1);
  ASSERT_FLOAT_EQ(m1(0, 1), 2);
  ASSERT_FLOAT_EQ(m1(1, 0), 0);
  ASSERT_FLOAT_EQ(m1(1, 1), 0);

  Matrix<2> m2 = {{1, 2}, {3, 4}, {5, 6}};
  ASSERT_FLOAT_EQ(m2(0, 0), 1);
  ASSERT_FLOAT_EQ(m2(0, 1), 2);
  ASSERT_FLOAT_EQ(m2(1, 0), 3);
  ASSERT_FLOAT_EQ(m2(1, 1), 4);
}

TEST(Matrix, useNestedListWithMixedSize) {
  Matrix<4> m = {{1, 2, 3, 4, 5}, {6, 7}, {8, 9, 10, 11}};
  ASSERT_FLOAT_EQ(m(0, 0), 1);
  ASSERT_FLOAT_EQ(m(0, 1), 2);
  ASSERT_FLOAT_EQ(m(0, 2), 3);
  ASSERT_FLOAT_EQ(m(0, 3), 4);
  ASSERT_FLOAT_EQ(m(1, 0), 6);
  ASSERT_FLOAT_EQ(m(1, 1), 7);
  ASSERT_FLOAT_EQ(m(1, 2), 0);
  ASSERT_FLOAT_EQ(m(1, 3), 0);
  ASSERT_FLOAT_EQ(m(2, 0), 8);
  ASSERT_FLOAT_EQ(m(2, 1), 9);
  ASSERT_FLOAT_EQ(m(2, 2), 10);
  ASSERT_FLOAT_EQ(m(2, 3), 11);
  ASSERT_FLOAT_EQ(m(3, 0), 0);
  ASSERT_FLOAT_EQ(m(3, 1), 0);
  ASSERT_FLOAT_EQ(m(3, 2), 0);
  ASSERT_FLOAT_EQ(m(3, 3), 0);
}

TEST(Matrix, isEqualToItself) {
  Matrix<> m;
  ASSERT_TRUE(m == m);
}

TEST(Matrix, isNotEqualToDifferentMatrix) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{5, 6}, {7, 8}};
  ASSERT_FALSE(m1 == m2);
  ASSERT_FALSE(m2 == m1);
}

TEST(Matrix, isEqualToVerySimilarMatrix) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{1, 2.0000001}, {3.000002, 4.0000009}};
  ASSERT_TRUE(m1 == m2);
  ASSERT_TRUE(m2 == m1);
}

TEST(Matrix, multiplyWithAnotherMatrix) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{5, 6}, {7, 8}};
  ASSERT_EQ(m1 * m2, (Matrix<2>{{19, 22}, {43, 50}}));
}

TEST(Matrix, multiplyWithTuple) {
  Matrix<2> m{{1, 2}, {3, 4}};
  Tuple<2> t{5, 6};
  ASSERT_EQ(m * t, (Tuple<2>{17, 39}));
}

TEST(Identity, multiplyWithIdentity) {
  Matrix<4> m{0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
  ASSERT_EQ(m * identity, m);
}

TEST(Transpose, transposeMatrix) {
  Matrix<4> m{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  ASSERT_EQ(
      transpose(m),
      (Matrix<4>{
          {1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}}));
}

TEST(Transpose, transposeIdentity) { ASSERT_EQ(transpose(identity), identity); }

TEST(Inverse, calculate2x2Determinant) {
  Matrix<2> m{1, 5, -3, 2};
  ASSERT_FLOAT_EQ(determinant(m), 17);
}

TEST(Inverse, getSubmatrixOf3x3Matrix) {
  Matrix<3> m{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
  ASSERT_EQ(submatrix(m, 0, 2), (Matrix<2>{{-3, 2}, {0, 6}}));
}

TEST(Inverse, getSubmatrixOf4x4Matrix) {
  Matrix<4> m{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}};
  ASSERT_EQ(submatrix(m, 2, 1),
            (Matrix<3>{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}));
}

TEST(Inverse, calculateMinorOf3x3Matrix) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  ASSERT_FLOAT_EQ(minor(m, 1, 0), 25);
}

TEST(Inverse, calculateCofactorOf3x3Matrix) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  ASSERT_FLOAT_EQ(cofactor(m, 0, 0), -12);
  ASSERT_FLOAT_EQ(cofactor(m, 1, 0), -25);
}
