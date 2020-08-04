#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <array>

template <std::size_t n = 2> struct Matrix {
  Matrix() { std::fill(values.begin(), values.end(), 0.); }

  double &operator()(std::size_t row, std::size_t column) {
    return values[row * n + column];
  }
  double operator()(std::size_t row, std::size_t column) const {
    return values[row * n + column];
  }

  std::array<double, n * n> values;
  static const std::size_t size;
};

template <std::size_t n> const std::size_t Matrix<n>::size = n;

#endif
