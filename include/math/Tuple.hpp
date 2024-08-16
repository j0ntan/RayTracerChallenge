#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>

#include <utility/Float_compare.hpp>

/**
 * @brief A `Tuple` represents an ordered list of numbers
 *
 * @tparam n The count of numerical values that define the `Tuple`
 */
template <std::size_t n = 0> struct Tuple {

  /**
   * @brief Construct a zero-initialized `Tuple`
   *
   */
  constexpr Tuple() : elements{} {};

  /**
   * @brief Construct a new `Tuple` object with the given list of values
   *
   * Initialize `elements` with the first `n` values in `list` or with zero.
   *
   * @param list Initial values for `elements`
   */
  Tuple(const std::initializer_list<double> &list) : elements{} {
    const auto COUNT = list.size() > n ? n : list.size();
    std::copy_n(list.begin(), COUNT, elements.begin());
  }

  /**
   * @brief Construct a new `Tuple` object with the given array of values
   *
   * @param array Initial values for `elements`
   */
  Tuple(const std::array<double, n> &array) { elements = array; }

  /**
   * @brief Access `Tuple` value with given index
   *
   * @param index The numerical position of the variable to access
   * @return double The stored value at `index`
   */
  double operator[](const std::size_t &index) const { return elements[index]; }

  /**
   * @brief Access `Tuple` value, by reference, with given index
   *
   * @param index The numerical position of the variable to access
   * @return double The stored value at `index`
   */
  double &operator[](const std::size_t &index) { return elements[index]; }

  /**
   *
   * Class members
   *
   */

  /**
   * @brief Contain the `n` elements that define the Tuple
   *
   */
  std::array<double, n> elements;
};

/**
 * @brief Overload the == operator
 *
 * Check `Tuple` for element-wise equality.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return true All corresponding elements are the same
 */
template <std::size_t n>
bool operator==(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  if (&lhs == &rhs)
    return true;

  return std::equal(lhs.elements.cbegin(), lhs.elements.cend(),
                    rhs.elements.cbegin(), float_equals);
}

/**
 * @brief Overload the + operator
 *
 * Create a `Tuple` using the element-wise sum of two other `Tuple` objects.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Tuple<n> Result of the element-wise sum
 */
template <std::size_t n>
Tuple<n> operator+(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::plus<double>());
  return result;
}

/**
 * @brief Overload the unary - operator
 *
 * Negate a `Tuple` by changing the sign of each element.
 *
 * @tparam n Size of the `Tuple`
 * @param tuple The instance being negated
 * @return Tuple<n> Result of negation
 */
template <std::size_t n> Tuple<n> operator-(const Tuple<n> &tuple) {
  Tuple<n> negated = tuple;
  std::transform(tuple.elements.cbegin(), tuple.elements.cend(),
                 negated.elements.begin(), std::negate<double>());
  return negated;
}

/**
 * @brief Overload the - operator
 *
 * Create a `Tuple` using the element-wise subtraction of two other `Tuple`
 * objects.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Tuple<n> Result of the element-wise subtraction
 */
template <std::size_t n>
Tuple<n> operator-(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::minus<double>());
  return result;
}

/**
 * @brief Overload the * operator
 *
 * Create a `Tuple` using the element-wise multiplication of two other `Tuple`
 * objects.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Tuple<n> Result of the element-wise multiplication
 */
template <std::size_t n>
Tuple<n> operator*(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 rhs.elements.cbegin(), result.elements.begin(),
                 std::multiplies<double>());
  return result;
}

/**
 * @brief Overload the * operator for scaling
 *
 * Scale a `Tuple` by multiplying each element by the scalar value.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs `Tuple` to be scaled
 * @param scalar Scalar value to be applied
 * @return Tuple<n> Resulting scaled `Tuple`
 */
template <std::size_t n>
Tuple<n> operator*(const Tuple<n> &lhs, double scalar) {
  Tuple<n> result;
  std::transform(lhs.elements.cbegin(), lhs.elements.cend(),
                 result.elements.begin(),
                 [=](double element) { return element * scalar; });
  return result;
}

/**
 * @brief Overload the * operator for scaling
 *
 * Scale a `Tuple` by multiplying each element by the scalar value.
 *
 * @tparam n Size of the `Tuple`
 * @param scalar Scalar value to be applied
 * @param rhs `Tuple` to be scaled
 * @return Tuple<n> Resulting scaled `Tuple`
 */
template <std::size_t n = 0>
Tuple<n> operator*(double scalar, const Tuple<n> &rhs) {
  return rhs * scalar;
}

/**
 * @brief Overload the / operator for scaling
 *
 * Scalar division divides each `Tuple` element by the scalar value.
 *
 * @tparam n Size of the `Tuple`
 * @param lhs `Tuple` to be divided
 * @param scalar Scalar value for division
 * @return Tuple<n> Resulting scaled `Tuple`
 */
template <std::size_t n>
Tuple<n> operator/(const Tuple<n> &lhs, double scalar) {
  return (1.0 / scalar) * lhs;
}

/**
 * @brief Calculate the inner product of two `Tuple` objects
 *
 * @tparam n Size of the `Tuple`
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return double Result of the inner product calculation
 */
template <std::size_t n>
double inner_product(const Tuple<n> &lhs, const Tuple<n> &rhs) {
  return std::inner_product(lhs.elements.cbegin(), lhs.elements.cend(),
                            rhs.elements.cbegin(), 0.);
}
