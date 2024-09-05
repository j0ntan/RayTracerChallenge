#pragma once

#include <algorithm>
#include <array>
#include <stdexcept>
#include <utility>

#include "Tuple.hpp"
#include <utility/Float_compare.hpp>

/**
 * @brief A utility class that allows working with square matrices
 *
 * @tparam n Dimension for an n x n matrix
 */
template <std::size_t n = 2> struct Matrix {

  /**
   * @brief Construct a new null Matrix object
   *
   */
  Matrix() : values{{0}} {}

  /**
   * @brief Construct a new initialized Matrix object
   *
   * The object is initialized using the first `n` values in the given
   * `simple_list` or zero otherwise.
   *
   * @param simple_list List of initial values
   */
  Matrix(std::initializer_list<double> simple_list) : values{{0}} {
    auto list_it = simple_list.begin();
    for (std::size_t row = 0; row < n && list_it != simple_list.end(); ++row)
      for (std::size_t col = 0; col < n && list_it != simple_list.end();
           ++col, ++list_it)
        values[row][col] = *list_it;
  }

  /**
   * @brief Construct a new initialized Matrix object
   *
   * The object is initialized using the first `n` values in the first `n` rows
   * of the given 'nested_list' or zero otherwise. If any row in `nested_list`
   * has more than `n` elements, the elements after the nth are discarded.
   *
   * @param nested_list Nested list of initialization values
   */
  Matrix(std::initializer_list<std::initializer_list<double>> nested_list)
      : values{{0}} {
    auto matrix_row_it = values.begin();
    auto list_row_it = nested_list.begin();
    for (; matrix_row_it != values.end() && list_row_it != nested_list.end();
         ++list_row_it, ++matrix_row_it)
      if (list_row_it->size() > 0) {
        const std::size_t COPY_AMOUNT =
            list_row_it->size() <= n ? list_row_it->size() : n;
        std::copy_n(list_row_it->begin(), COPY_AMOUNT, matrix_row_it->begin());
      }
  }

  /**
   * @brief Overload the () operator for element access
   *
   * Access the element at the `row` and `column` indices, by reference.
   *
   * @param row Row to access
   * @param column Column to access
   * @return double& The accessed element
   */
  double &operator()(std::size_t row, std::size_t column) {
    return values[row][column];
  }

  /**
   * @brief Overload the () operator for element access
   *
   * Access the element at the `row` and `column` indices, by value.
   *
   * @param row Row to access
   * @param column Column to access
   * @return double The accessed element
   */
  double operator()(std::size_t row, std::size_t column) const {
    return values[row][column];
  }

  /**
   * @brief Create array using matrix values
   *
   * This function essentially "flattens" the matrix from an NxN size to a
   * 1xN^2 size. It is mainly used in the unit tests to more easily verify the
   * matrix contents.
   *
   * @return std::array<double, n * n> An array containing element values
   */
  std::array<double, n * n> toArray() const {
    std::array<double, n * n> result{};
    for (std::size_t row = 0, i = 0; row < n; ++row)
      for (std::size_t col = 0; col < n; ++col, ++i)
        result[i] = values[row][col];

    return result;
  }

  /**
   *
   * Class members
   *
   */

  /**
   * @brief A 2D array container for the matrix values
   *
   */
  std::array<std::array<double, n>, n> values;
};

/**
 * @brief Overload the == operator
 *
 * Check `Matrix` pair for element-wise equality.
 *
 * @tparam n Size of the matrix
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return true All corresponding elements are the same
 */
template <std::size_t n>
bool operator==(const Matrix<n> &lhs, const Matrix<n> &rhs) {
  if (&lhs == &rhs)
    return true;

  for (std::size_t row = 0; row < n; ++row)
    for (std::size_t col = 0; col < n; ++col)
      if (!float_equals(lhs.values[row][col], rhs.values[row][col]))
        return false;

  return true;
}

/**
 * @brief Overload the != operator
 *
 * * Check the matrix for element-wise inequality.
 *
 * @tparam n Size of the matrix
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return true At least one pair of corresponding elements are different
 */
template <std::size_t n>
bool operator!=(const Matrix<n> &lhs, const Matrix<n> &rhs) {
  return !(lhs == rhs);
}

/**
 * @brief Overload the * operator for 2 `Matrix` objects
 *
 * Perform a mathematical matrix multiplication of the two object values.
 *
 * @tparam n Size of the matrix
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Matrix Result of matrix multiplication
 */
template <std::size_t n>
Matrix<n> operator*(const Matrix<n> &lhs, const Matrix<n> &rhs) {
  Matrix<n> result;

  for (size_t row = 0; row < n; ++row)
    for (size_t col = 0; col < n; ++col)
      for (size_t pair = 0; pair < n; ++pair)
        result(row, col) += lhs(row, pair) * rhs(pair, col);

  return result;
}

/**
 * @brief Overload the * operator for a `Matrix` & `Tuple` pair
 *
 * This operator performs a multiplication similar to the mathematical
 * multiplication of an NxN matrix and a Nx1 vector, producing another Nx1
 * vector result.
 *
 * @tparam n Size of the matrix
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Tuple<n> Resulting vector of matrix multiplication
 */
template <std::size_t n>
Tuple<n> operator*(const Matrix<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  for (std::size_t index = 0; index < n; ++index)
    for (std::size_t pair = 0; pair < n; ++pair)
      result[index] += lhs(index, pair) * rhs[pair];
  return result;
}

/**
 * @brief Produce the mathematical transpose `Matrix` of the given `Matrix`
 *
 * @tparam n Size of the matrix
 * @param matrix The object being transposed
 * @return Matrix<n> The resulting transposed matrix
 */
template <std::size_t n> Matrix<n> transpose(const Matrix<n> &matrix) {
  Matrix<n> result(matrix);
  for (std::size_t diagonal_index = 0; diagonal_index < n; ++diagonal_index)
    for (std::size_t swap_index = 0; swap_index < diagonal_index; ++swap_index)
      std::swap(result(diagonal_index, swap_index),
                result(swap_index, diagonal_index));
  return result;
}

/**
 * @brief Calculate the determinant of a 2x2 `Matrix` object
 *
 * @param matrix The matrix argument for the determinant calculation
 * @return double The mathematical determinant calculation
 */
double determinant(const Matrix<2> &matrix);

/**
 * @brief Create a submatrix by removing a row and column of a given matrix
 *
 * @tparam n Size of the matrix
 * @param matrix Matrix used to create the submatrix
 * @param row_delete Row to be removed
 * @param column_delete Column to be removed
 * @return Matrix<n - 1> The submatrix object
 */
template <std::size_t n>
Matrix<n - 1> submatrix(const Matrix<n> &matrix, std::size_t row_delete,
                        std::size_t column_delete) {
  Matrix<n - 1> result;
  for (std::size_t row = 0, row_result = 0; row < n; ++row)
    if (row != row_delete) {
      for (std::size_t col = 0, col_result = 0; col < n; ++col)
        if (col != column_delete) {
          result(row_result, col_result) = matrix(row, col);
          ++col_result;
        }
      ++row_result;
    }
  return result;
}

/**
 * @brief Calculate the mathematical minor of the given `matrix` using the given
 * `row` and `column`
 *
 * @tparam n Size of the matrix
 * @param matrix Matrix used to calculate the minor
 * @param row Row used to calculate the minor
 * @param column Column used to calculate the minor
 * @return double Resulting minor calculation
 */
template <std::size_t n>
double minor(const Matrix<n> &matrix, std::size_t row, std::size_t column) {
  return determinant(submatrix(matrix, row, column));
}

/**
 * @brief Calculate the mathematical cofactor of the given `matrix` using the
 * given `row` and `column`
 *
 * @tparam n Size of the matrix
 * @param matrix Matrix used to calculate the cofactor
 * @param row Row used to calculate the cofactor
 * @param column Column used to calculate the cofactor
 * @return double Resulting cofactor calculation
 */
template <std::size_t n>
double cofactor(const Matrix<n> &matrix, std::size_t row, std::size_t column) {
  // negate the minor value when `row` + `column` is odd
  return (((row + column) % 2 == 0) ? 1 : -1) * minor(matrix, row, column);
}

/**
 * @brief Calculate the determinant of an NxN `Matrix` object
 *
 * @tparam n Size of the matrix
 * @param matrix The matrix argument for the determinant calculation
 * @return double The mathematical determinant calculation
 */
template <std::size_t n> double determinant(const Matrix<n> &matrix) {
  double result = 0.;
  for (std::size_t index = 0; index < n; ++index)
    result += matrix(0, index) * cofactor(matrix, 0, index);
  return result;
}

/**
 * @brief Create an inverse `Matrix` of the given `Matrix` object
 *
 * @tparam n Size of the matrix
 * @param matrix Matrix used to create the inverse object
 * @throw std::domain_error Throws an exception when the given `matrix` is not
 * invertible
 * @return Matrix<n> The inverse matrix of the given `matrix` object
 */
template <std::size_t n> Matrix<n> inverse(const Matrix<n> &matrix) {
  const auto DETERMINANT = determinant(matrix);
  if (DETERMINANT == 0)
    throw std::domain_error("Cannot invert this matrix.\n");

  Matrix<n> result;
  for (std::size_t row = 0; row < n; ++row)
    for (std::size_t column = 0; column < n; ++column)
      result(column, row) = cofactor(matrix, row, column) / DETERMINANT;

  return result;
}

/**
 * @brief A pre-defined constant 4x4 identity `Matrix` object
 *
 */
const Matrix<4> IDENTITY{
    {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
