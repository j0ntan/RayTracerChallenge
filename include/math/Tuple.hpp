#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <utility/Float_compare.hpp>

template <std::size_t n = 0> struct Tuple {
  Tuple() = default;
  Tuple(const std::initializer_list<double> &list) {
    std::copy(list.begin(), list.begin() + (n <= list.size() ? n : list.size()),
              elements.begin());
  }
  Tuple(const std::array<double, n> &array) { elements = array; }

  double operator[](const std::size_t &index) const { return elements[index]; }
  double &operator[](const std::size_t &index) { return elements[index]; }

  std::array<double, n> elements;
  static constexpr std::size_t size = n;
};

template <std::size_t n>
bool operator==(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  if (&lhs == &rhs)
    return true;

  return std::equal(lhs.elements.cbegin(), lhs.elements.cend(),
                    rhs.elements.cbegin(), float_equals);
}

template <std::size_t n>
Tuple<n> operator+(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::plus<double>());
  return result;
}

template <std::size_t n>
Tuple<n> operator-(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::minus<double>());
  return result;
}

template <std::size_t n>
Tuple<n> operator*(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::multiplies<double>());
  return result;
}

template <std::size_t n>
Tuple<n> operator*(const Tuple<n> &lhs, double scalar) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 result.elements.begin(),
                 [=](double element) { return element * scalar; });
  return result;
}

template <std::size_t n = 0>
Tuple<n> operator*(double scalar, const Tuple<n> &rhs) {
  return rhs * scalar;
}

template <std::size_t n>
Tuple<n> operator/(const Tuple<n> &lhs, double scalar) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 result.elements.begin(),
                 [=](double element) { return element / scalar; });
  return result;
}

template <std::size_t n>
double inner_product(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  return std::inner_product(lhs.elements.cbegin(), lhs.elements.cend(),
                            rhs.elements.cbegin(), 0.);
}

#endif
