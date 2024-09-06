#pragma once

#include <math/Tuple.hpp>

/**
 * @brief Represents an RGB color value
 *
 * Note: The book recommends to not put any restrictions on the `Color`
 * component values. Normally, RGB values are in the range of 0-255 but this
 * class uses a range of 0.0-1.0, where these are soft limits and values can go
 * out of this range. According to the book, a color may go through multiple
 * transformations before reaching the virtual 'eye', causing it to fall out of
 * range. Limiting the color prematurely can make parts of a scene too bright or
 * too dark.
 *
 */
struct Color final : public Tuple<3> {
  /**
   * @brief Construct a default Color object
   *
   * Creates a black color by default, with RGB values of 0,0,0.
   *
   */
  Color();

  /**
   * @brief Construct a new Color object with initial RGB values
   *
   * @param r Red component
   * @param g Green component
   * @param b Blue component
   */
  Color(double r, double g, double b);

  /**
   * @brief Construct a new Color object with RGB values given by a `Tuple`
   *
   * @param values The initial RGB values
   */
  Color(const Tuple<3> &values);

  /**
   * @brief Overload the assignment operator
   *
   * @param rhs Color used to assign RGB values
   * @return Color& Re-assigned color
   */
  Color &operator=(const Color &rhs) = default;

  /**
   * @brief Accessor functions for each `Color` component
   *
   * @return double&, double The accessed component returned by reference or by
   * value, respectively
   */
  double &red();
  double &green();
  double &blue();
  double red() const;
  double green() const;
  double blue() const;
};

/**
 * @brief Overload the + operator for two `Color` objects
 *
 * Create a `Color` using the element-wise sum of two other `Color` objects.
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Color Result of the element-wise sum
 */
Color operator+(const Color &lhs, const Color &rhs);

/**
 * @brief Overload the - operator for two `Color` objects
 *
 * Create a `Color` using the element-wise subtraction of two other `Color`
 * objects.
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Color Result of the element-wise subtraction
 */
Color operator-(const Color &lhs, const Color &rhs);

/**
 * @brief Overload the * operator for a `Color` and a scalar
 *
 * Create a `Color` by multiplying each component of a given `Color` by the
 * scalar amount.
 *
 * @param color Given color values
 * @param scalar Given scalar value
 * @return Color Color with scaled values
 */
Color operator*(const Color &color, double scalar);

/**
 * @brief Overload the * operator for a `Color` and a scalar
 *
 * Create a `Color` by multiplying each component of a given `Color` by the
 * scalar amount.
 *
 * @param scalar Given scalar value
 * @param color Given color values
 * @return Color Color with scaled values
 */
Color operator*(double scalar, const Color &color);

/**
 * @brief Overload the * operator for two `Color` objects
 *
 * Create a `Color` using the element-wise product of two other `Colors`
 * objects. Also known as the Hadamard product or Schur product.
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Color Result of the element-wise product
 */
Color operator*(const Color &lhs, const Color &rhs);
