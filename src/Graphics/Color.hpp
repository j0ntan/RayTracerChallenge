#pragma once

#include <Math/Tuple.hpp>

/**
 * @brief Represents a ray tracer pixel as an RGB color object
 *
 * The color components are a set of three floating-point numbers in the range
 * [0, 1]. The values may go above the upper limit due to effects in the ray
 * tracer, but a value of 1.0 becomes scaled to 255 as the maximum value for
 * the color channel.
 *
 */
class Color : public Tuple
{
public:
    /**
     * @brief Construct a zero-initialized color, equivalent to black
     *
     */
    Color() = default;

    /**
     * @brief Construct a color object with initial values
     *
     * @param red The red component
     * @param green The green component
     * @param blue The blue component
     */
    Color(double red, double green, double blue);

    /**
     * @brief Construct a color object from a tuple's first three components
     *
     * @param tuple
     */
    Color(const Tuple &tuple);

    /**
     * @brief Access the red component value
     *
     * @return double The red value
     */
    double red() const;

    /**
     * @brief Access the green component value
     *
     * @return double The green value
     */
    double green() const;

    /**
     * @brief Access the blue component value
     *
     * @return double The blue value
     */
    double blue() const;

private:
    // make inaccessible from the Color interface
    using Tuple::w;
    using Tuple::x;
    using Tuple::y;
    using Tuple::z;
};

/**
 * @brief Overload the == operator
 *
 * @param lhs The left-hand side color
 * @param rhs The right-hand side color
 * @return true If all corresponding components are equal
 * @return false If any corresponding components are not equal
 */
bool operator==(const Color &lhs, const Color &rhs);

/**
 * @brief Overload the + operator
 *
 * @param lhs The left-hand side color
 * @param rhs The right-hand side color
 * @return Color Result of the component-wise sum
 */
Color operator+(const Color &lhs, const Color &rhs);

/**
 * @brief Overload the - operator
 *
 * @param lhs The left-hand side color
 * @param rhs The right-hand side color
 * @return Color Result of the component-wise subtraction
 */
Color operator-(const Color &lhs, const Color &rhs);

/**
 * @brief Overload the * operator for scaling
 *
 * @param color The color to be scaled
 * @param scalar Scalar value to be applied
 * @return Color Resulting scaled color
 */
Color operator*(const Color &color, double scalar);

/**
 * @brief Overload the * operator for scaling
 *
 * @param scalar Scalar value to be applied
 * @param color The color to be scaled
 * @return Color Resulting scaled color
 */
Color operator*(double scalar, const Color &color);

/**
 * @brief Overload the * operator for multiplying colors
 *
 * @param lhs The left-hand side color
 * @param rhs The right-hand side color
 * @return Color Result of the component-wise multiplication
 */
Color operator*(const Color &lhs, const Color &rhs);
