#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Tuple.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>
#include <utility/Float_compare.hpp>
#include <utility>

template <std::size_t n = 2> struct Matrix {
  Matrix() : values{{0}} {}
  Matrix(std::initializer_list<double> simple_list) : values{{0}} {
    auto list_it = simple_list.begin();
    for (std::size_t row = 0; row < n && list_it != simple_list.end(); ++row)
      for (std::size_t col = 0; col < n && list_it != simple_list.end();
           ++col, ++list_it)
        values[row][col] = *list_it;
  }
  Matrix(std::initializer_list<std::initializer_list<double>> nested_list)
      : values{{0}} {
    auto dest_row_it = values.begin();
    auto src_row_it = nested_list.begin();
    for (; src_row_it != nested_list.end(); ++src_row_it, ++dest_row_it)
      if (src_row_it->size() > 0) {
        const std::size_t copy_amount =
            src_row_it->size() <= n ? src_row_it->size() : n;
        std::copy_n(src_row_it->begin(), copy_amount, dest_row_it->begin());
      }
  }

  bool operator==(const Matrix &rhs) const {
    if (this == &rhs)
      return true;

    return std::equal(
        values.begin(), values.end(), rhs.values.begin(),
        [](const std::array<double, n> &lhs, const std::array<double, n> &rhs) {
          return std::equal(lhs.begin(), lhs.end(), rhs.begin(), float_equals);
        });
  }

  double &operator()(std::size_t row, std::size_t column) {
    return values[row][column];
  }
  double operator()(std::size_t row, std::size_t column) const {
    return values[row][column];
  }

  Matrix operator*(const Matrix &rhs) const {
    auto &lhs = *this;
    Matrix<n> result;

    for (size_t row = 0; row < n; ++row)
      for (size_t col = 0; col < n; ++col)
        for (size_t pair = 0; pair < n; ++pair)
          result(row, col) += lhs(row, pair) * rhs(pair, col);

    return result;
  }

  std::array<std::array<double, n>, n> values;
  static const std::size_t size;
};

template <std::size_t n> const std::size_t Matrix<n>::size = n;

template <std::size_t n>
Tuple<n> operator*(const Matrix<n> &lhs, Tuple<n> &rhs) {
  Tuple<n> result;
  for (std::size_t index = 0; index < n; ++index)
    for (std::size_t pair = 0; pair < n; ++pair)
      result[index] += lhs(index, pair) * rhs[pair];
  return result;
}

template <std::size_t n> Matrix<n> transpose(const Matrix<n> &matrix) {
  Matrix<n> result(matrix);
  for (std::size_t diagonal_index = 0; diagonal_index < n; ++diagonal_index)
    for (std::size_t swap_index = 0; swap_index < diagonal_index; ++swap_index)
      std::swap(result(diagonal_index, swap_index),
                result(swap_index, diagonal_index));
  return result;
}
double determinant(const Matrix<2> &matrix) {
  return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
}
template <std::size_t n>
Matrix<n - 1> submatrix(const Matrix<n> &matrix, std::size_t row,
                        std::size_t column) {
  Matrix<n - 1> result;
  for (std::size_t i = 0, result_i = 0; i < n; ++i)
    if (i != row) {
      for (std::size_t j = 0, result_j = 0; j < n; ++j)
        if (j != column) {
          result(result_i, result_j) = matrix(i, j);
          ++result_j;
        }
      ++result_i;
    }
  return result;
}
template <std::size_t n>
double minor(const Matrix<n> &matrix, std::size_t row, std::size_t column) {
  return determinant(submatrix(matrix, row, column));
}
template <std::size_t n>
double cofactor(const Matrix<n> &matrix, std::size_t row, std::size_t column) {
  return ((row + column) % 2 == 0 ? 1 : -1) * minor(matrix, row, column);
}
template <std::size_t n> double determinant(const Matrix<n> &matrix) {
  double result = 0.;
  for (std::size_t index = 0; index < n; ++index)
    result += matrix(0, index) * cofactor(matrix, 0, index);
  return result;
}
template <std::size_t n> Matrix<n> inverse(const Matrix<n> &matrix) {
  const auto det = determinant(matrix);
  if (det == 0)
    throw std::domain_error("Cannot invert this matrix.\n");

  Matrix<n> result;
  for (std::size_t row = 0; row < n; ++row)
    for (std::size_t column = 0; column < n; ++column)
      result(column, row) = cofactor(matrix, row, column) / det;

  return result;
}

const Matrix<4> identity{
    {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

#endif
