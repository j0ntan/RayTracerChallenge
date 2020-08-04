#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <array>
#include <utility>

template <std::size_t n = 2> struct Matrix {
  Matrix() { std::fill(values.begin(), values.end(), 0.); }
  Matrix(std::initializer_list<double> simple_list) {
    const auto initialization_count =
        n * n <= simple_list.size() ? n * n : simple_list.size();
    std::copy(simple_list.begin(), simple_list.begin() + initialization_count,
              values.begin());

    if (initialization_count < n * n)
      std::fill_n(values.begin() + initialization_count,
                  n * n - initialization_count, 0.);
  }
  Matrix(std::initializer_list<std::initializer_list<double>> nested_list) {
    auto inner_list_it = nested_list.begin();
    const double *value_it;
    std::size_t index = 0;

    std::size_t list_count = n <= nested_list.size() ? n : nested_list.size();
    for (std::size_t row = 0; row < list_count; ++row, ++inner_list_it) {
      value_it = inner_list_it->begin();
      for (std::size_t column = 0; column < n; ++column, ++value_it, ++index) {
        if (column < inner_list_it->size())
          values[index] = *value_it;
        else
          values[index] = 0;
      }
    }

    if (index < n * n)
      std::fill_n(values.begin() + index, (n * n - index), 0);
  }

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
