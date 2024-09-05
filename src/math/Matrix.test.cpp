#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(MatrixConstructor, constructDefaultObject) { Matrix<> m; }

TEST(MatrixArray, convertToArray) {
  Matrix<> m;
  std::array<double, 4> list = m.toArray();
}

TEST(MatrixConstructor, matchDefaultObjectValues) {
  Matrix<> m;
  std::array<double, 4> zeroed_array{};
  ASSERT_EQ(m.toArray(), zeroed_array);
}

TEST(MatrixConstructor, constructWithGivenSize) { Matrix<3> m; }

TEST(MatrixIndexOperator, callOperator) {
  Matrix<> m;
  m(0, 0);
}

TEST(MatrixIndexOperator, accessValueAtIndex) {
  Matrix<> m;
  auto value = m(0, 0);
}

TEST(MatrixIndexOperator, overwriteValue) {
  Matrix<> m;
  m(0, 0) = 1;
}

TEST(MatrixIndexOperator, matchOverwrittenValue) {
  Matrix<> m;
  ASSERT_EQ(m(0, 0), 0); // confirm default value

  m(0, 0) = 1;           // overwrite
  ASSERT_EQ(m(0, 0), 1); // confirm overwrite
}

TEST(MatrixIndexOperator, matchAllValuesAfterOverwrite) {
  Matrix<> m;
  std::array<double, 4> zeroed_array{};
  std::array<double, 4> expected_first_overwrite{1, 0, 0, 0};
  std::array<double, 4> expected_second_overwrite{1, 2, 0, 0};
  std::array<double, 4> expected_third_overwrite{1, 2, 753, 0};
  std::array<double, 4> expected_fourth_overwrite{1, 2, 753, 0.843};

  ASSERT_EQ(m.toArray(), zeroed_array); // confirm all initial values are zero

  m(0, 0) = 1;
  ASSERT_EQ(m.toArray(), expected_first_overwrite);

  m(0, 1) = 2;
  ASSERT_EQ(m.toArray(), expected_second_overwrite);

  m(1, 0) = 753;
  ASSERT_EQ(m.toArray(), expected_third_overwrite);

  m(1, 1) = 0.843;
  ASSERT_EQ(m.toArray(), expected_fourth_overwrite);
}

TEST(MatrixConstructor, matchZeroValuesForExplicitlySizedDefaultMatrix) {
  Matrix<4> m;
  std::array<double, 16> zeroed_array{};
  ASSERT_EQ(m.toArray(), zeroed_array);
}

TEST(MatrixListConstructor, constructWithSimpleList) {
  Matrix<2> m{1, 2, 3, 4};
}

TEST(MatrixListConstructor, matchSimpleListValues) {
  Matrix<2> m{1, 2, 3, 4};
  std::array<double, 4> expected_array{1, 2, 3, 4};
  ASSERT_EQ(m.toArray(), expected_array);
}

TEST(MatrixListConstructor, constructWithIncompleteList) {
  Matrix<2> normally_takes_4_arguments{1};
}

TEST(MatrixListConstructor, matchExpectedValuesForIncompleteList) {
  Matrix<2> m{1};
  std::array<double, 4> expected_array{1, 0, 0, 0};
  ASSERT_EQ(m.toArray(), expected_array);
}

TEST(MatrixListConstructor, constructWithOversizedList) {
  Matrix<2> normally_takes_4_arguments{1, 2, 3, 4, 5, 6};
}

TEST(MatrixListConstructor, matchExpectedValuesForOversizedList) {
  Matrix<2> m = {2, 4, 6, 8, 10, 12};
  std::array<double, 4> expected_array{2, 4, 6, 8};
  ASSERT_EQ(m.toArray(), expected_array);
}

TEST(MatrixNestedListConstructor, constructObject) {
  Matrix<2> m = {{1, 2}, {3, 4}};
}

TEST(MatrixNestedListConstructor, matchNestedListValues) {
  Matrix<2> m = {{1, 2}, {3, 4}};
  std::array<double, 4> expected_array{1, 2, 3, 4};
  ASSERT_EQ(m.toArray(), expected_array);
}

TEST(MatrixNestedListConstructor, constructWithNestedListOfIncorrectSize) {
  Matrix<2> row_is_missing_one_argument = {{0}, {0, 0}};
  Matrix<2> row_has_an_extra_argument = {{0, 0}, {0, 0, 0}};
}

TEST(MatrixNestedListConstructor, matchValuesForImproperNestedLists) {
  Matrix<2> m1{{1}, {3, 4}};
  Matrix<2> m2{{1, 2}, {3, 4, 5}};
  std::array<double, 4> expected_array1{1, 0, 3, 4};
  std::array<double, 4> expected_array2{1, 2, 3, 4};

  ASSERT_EQ(m1.toArray(), expected_array1);
  ASSERT_EQ(m2.toArray(), expected_array2);
}

TEST(MatrixNestedListConstructor, constructWithIncorrectListCount) {
  Matrix<4> arg_missing_2_lists = {{1, 2, 3, 4}, {5, 6, 7, 8}},
            arg_has_extra_list = {{1, 2, 3, 4},
                                  {5, 6, 7, 8},
                                  {9, 10, 11, 12},
                                  {13, 14, 15, 16},
                                  {17, 18, 19, 20}};
}

TEST(MatrixNestedListConstructor, matchValuesForImproperListCount) {
  Matrix<4> arg_missing_2_lists = {{1, 2, 3, 4}, {5, 6, 7, 8}},
            arg_has_extra_list = {{1, 2, 3, 4},
                                  {5, 6, 7, 8},
                                  {9, 10, 11, 12},
                                  {13, 14, 15, 16},
                                  {17, 18, 19, 20}};
  std::array<double, 16> expected_array1{1, 2, 3, 4, 5, 6, 7, 8,
                                         0, 0, 0, 0, 0, 0, 0, 0},
      expected_array2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  ASSERT_EQ(arg_missing_2_lists.toArray(), expected_array1);
  ASSERT_EQ(arg_has_extra_list.toArray(), expected_array2);
}

TEST(MatrixNestedListConstructor, constructWithMixedImproperLists) {
  // incomplete count of nested lists, first nested list has extra value, second
  // nested list has incomplete value count
  Matrix<4> m = {{1, 2, 3, 4, 5}, {6, 7}, {8, 9, 10, 11}};
}

TEST(MatrixNestedListConstructor, matchValuesForMixedImproperLists) {
  Matrix<4> m = {{1, 2, 3, 4, 5}, {6, 7}, {8, 9, 10, 11}};
  std::array<double, 16> expected_array{1, 2, 3,  4,  6, 7, 0, 0,
                                        8, 9, 10, 11, 0, 0, 0, 0};

  ASSERT_EQ(m.toArray(), expected_array);
}

TEST(MatrixEqualityOperator, callOperator) {
  Matrix<> m1, m2;
  bool result1 = m1 == m2;
  bool result2 = m2 == m1;
}

TEST(MatrixEqualityOperator, isEqualToItself) {
  Matrix<> m;
  ASSERT_TRUE(m == m);
}

TEST(MatrixEqualityOperator, isNotEqualToDifferentMatrix) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{5, 6}, {7, 8}};
  ASSERT_FALSE(m1 == m2);
  ASSERT_FALSE(m2 == m1);
}

TEST(MatrixEqualityOperator, isEqualToVerySimilarMatrix) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{1, 2.0000001}, {3.000002, 4.0000009}};

  // Note: The `EPSILON` value in the `Float_compare` file is used to check
  // equality of two float nums
  ASSERT_TRUE(m1 == m2);
  ASSERT_TRUE(m2 == m1);
}

TEST(MatrixInequalityOperator, callOperator) {
  Matrix<> m1, m2;
  bool result1 = m1 != m2;
  bool result2 = m2 != m1;
}

TEST(MatrixInequalityOperator, testOppositeCasesToEqualityTests) {
  Matrix<> m1{{1, 2}, {3, 4}}, m2{{5, 6}, {7, 8}},
      m3{{1, 2.0000001}, {3.000002, 4.0000009}};

  ASSERT_FALSE(m1 != m1);

  ASSERT_TRUE(m1 != m2);
  ASSERT_TRUE(m2 != m1);

  ASSERT_FALSE(m1 != m3);
  ASSERT_FALSE(m3 != m1);
}

TEST(MatrixMatrixMultiplicationOperator, callOperator) {
  Matrix<> m1, m2;
  Matrix<> result1 = m1 * m2;
  Matrix<> result2 = m2 * m1;
}

TEST(MatrixMatrixMultiplicationOperator, matchValuesForMatrixMultiplication) {
  Matrix<2> m1{{1, 2}, {3, 4}}, m2{{5, 6}, {7, 8}};
  Matrix<2> expected1{{19, 22}, {43, 50}}, expected2{{23, 34}, {31, 46}};

  ASSERT_EQ(m1 * m2, expected1);
  ASSERT_EQ(m2 * m1, expected2);
}

TEST(MatrixTupleMultiplicationOperator, callOperator) {
  Matrix<2> m;
  Tuple<2> t;
  Tuple<2> result = m * t;
}

TEST(MatrixTupleMultiplicationOperator, matchExpectedValues) {
  Matrix<2> m{{1, 2}, {3, 4}};
  Tuple<2> t{5, 6}, expected{17, 39};
  ASSERT_EQ(m * t, expected);
}

TEST(MatrixIdentity, callObject) { IDENTITY; }

TEST(MatrixIdentity, matchExpectedValues) {
  for (int row = 0; row < 4; ++row)
    for (int column = 0; column < 4; ++column)
      if (row == column)
        ASSERT_EQ(IDENTITY(row, column), 1);
      else
        ASSERT_EQ(IDENTITY(row, column), 0);
}

TEST(MatrixIdentity, multiplyMatrixAndPreserveValues) {
  Matrix<4> m{0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
  ASSERT_EQ(m * IDENTITY, m);
}

TEST(MatrixTranspose, callFunction) {
  Matrix<3> m;
  Matrix<3> result = transpose(m);
}

TEST(MatrixTranspose, matchTransposeValues) {
  Matrix<4> m{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
      expected{{1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}};
  ASSERT_EQ(transpose(m), expected);
}

TEST(MatrixTranspose, equateIdentityMatrixWithTranspose) {
  ASSERT_EQ(transpose(IDENTITY), IDENTITY);
}

TEST(MatrixInverse, callDeterminantFunctions) {
  Matrix<2> m1;
  Matrix<3> m2;
  double result1 = determinant(m1), result2 = determinant(m2);
}

TEST(MatrixInverse, match2x2Determinant) {
  Matrix<2> m{1, 5, -3, 2};
  ASSERT_FLOAT_EQ(determinant(m), 17);
}

TEST(MatrixInverse, match3x3Determinant) {
  Matrix<3> m{1, -2, 3, 2, 0, 3, 1, 5, 4};
  ASSERT_FLOAT_EQ(determinant(m), 25);
}

TEST(MatrixInverse, callSubmatrixFunction) {
  Matrix<3> m;
  std::size_t row_to_eliminate = 0, col_to_eliminate = 0;
  Matrix<2> result = submatrix(m, row_to_eliminate, col_to_eliminate);
}

TEST(MatrixInverse, getSubmatrixOf3x3Matrix) {
  Matrix<3> m{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
  std::size_t row_to_eliminate = 0, col_to_eliminate = 2;
  Matrix<2> expected{{-3, 2}, {0, 6}};
  ASSERT_EQ(submatrix(m, row_to_eliminate, col_to_eliminate), expected);
}

TEST(MatrixInverse, getSubmatrixOf4x4Matrix) {
  Matrix<4> m{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}};
  std::size_t row_to_eliminate = 2, col_to_eliminate = 1;
  Matrix<3> expected{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}};
  ASSERT_EQ(submatrix(m, row_to_eliminate, col_to_eliminate), expected);
}

TEST(MatrixInverse, callMinorFunction) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  double result = minor(m, 1, 0);
}

TEST(MatrixInverse, calculateMinorOf3x3Matrix) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  double expected = 25;
  ASSERT_FLOAT_EQ(minor(m, 1, 0), expected);
}

TEST(MatrixInverse, callCofactorFunction) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  double result = cofactor(m, 1, 0);
}

TEST(MatrixInverse, calculateCofactorOf3x3Matrix) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  ASSERT_FLOAT_EQ(cofactor(m, 0, 0), -12);
  ASSERT_FLOAT_EQ(cofactor(m, 1, 0), -25);
}

TEST(MatrixInverse, calculateDeterminantOfLargerMatrices) {
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

TEST(MatrixInverse, callInverseFunction) {
  Matrix<3> m{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};
  Matrix<3> result = inverse(m);
}

TEST(MatrixInverse, throwExceptionWhenNotInvertible) {
  Matrix<3> m{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_FLOAT_EQ(determinant(m), 0); // indicates not invertible
  EXPECT_THROW(inverse(m), std::domain_error);
}

TEST(MatrixInverse, calculateInverseMatrices) {
  Matrix<4> m1{{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}};
  Matrix<4> m2{{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}};
  Matrix<4> m3{{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}};
  Matrix<4> expected1{{.21805, .45113, .24060, -.04511},
                      {-.80827, -1.45677, -.44361, .52068},
                      {-.07895, -.22368, -.05263, .19737},
                      {-.52256, -.81391, -.30075, .30639}};
  Matrix<4> expected2{{-.15385, -.15385, -.28205, -.53846},
                      {-.07692, .12308, .02564, .03077},
                      {.35897, .35897, .43590, .92308},
                      {-.69231, -.69231, -.76923, -1.92308}};
  Matrix<4> expected3{{-.04074, -.07778, .14444, -.22222},
                      {-.07778, .03333, .36667, -.33333},
                      {-.02901, -.14630, -.10926, .12963},
                      {.17778, .06667, -.26667, .33333}};

  ASSERT_EQ(inverse(m1), expected1);
  ASSERT_EQ(inverse(m2), expected2);
  ASSERT_EQ(inverse(m3), expected3);
}

TEST(MatrixInverse, getOriginalMatrixUsingInverse) {
  Matrix<4> A{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}};
  Matrix<4> B{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}};
  ASSERT_EQ((A * B) * inverse(B), A);
}
