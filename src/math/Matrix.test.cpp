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

TEST(Inverse, calculateDeterminantOfLargerMatrices) {
  Matrix<3> m1{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}};
  ASSERT_FLOAT_EQ(cofactor(m1, 0, 0), 56);
  ASSERT_FLOAT_EQ(cofactor(m1, 0, 1), 12);
  ASSERT_FLOAT_EQ(cofactor(m1, 0, 2), -46);
  ASSERT_FLOAT_EQ(determinant(m1), -196);

  Matrix<4> m2{{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}};
  ASSERT_FLOAT_EQ(cofactor(m2, 0, 0), 690);
  ASSERT_FLOAT_EQ(cofactor(m2, 0, 1), 447);
  ASSERT_FLOAT_EQ(cofactor(m2, 0, 2), 210);
  ASSERT_FLOAT_EQ(cofactor(m2, 0, 3), 51);
  ASSERT_FLOAT_EQ(determinant(m2), -4071);
}

TEST(Inverse, calculateInverseMatrices) {
  Matrix<4> m1{{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}};
  ASSERT_EQ(inverse(m1), (Matrix<4>{{.21805, .45113, .24060, -.04511},
                                    {-.80827, -1.45677, -.44361, .52068},
                                    {-.07895, -.22368, -.05263, .19737},
                                    {-.52256, -.81391, -.30075, .30639}}));

  Matrix<4> m2{{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}};
  ASSERT_EQ(inverse(m2), (Matrix<4>{{-.15385, -.15385, -.28205, -.53846},
                                    {-.07692, .12308, .02564, .03077},
                                    {.35897, .35897, .43590, .92308},
                                    {-.69231, -.69231, -.76923, -1.92308}}));

  Matrix<4> m3{{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}};
  ASSERT_EQ(inverse(m3), (Matrix<4>{{-.04074, -.07778, .14444, -.22222},
                                    {-.07778, .03333, .36667, -.33333},
                                    {-.02901, -.14630, -.10926, .12963},
                                    {.17778, .06667, -.26667, .33333}}));
}

TEST(Inverse, getOriginalMatrixUsingInverse) {
  Matrix<4> A{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}};
  Matrix<4> B{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}};
  ASSERT_EQ((A * B) * inverse(B), A);
}
