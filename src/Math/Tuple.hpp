#pragma once

#include <array>

/**
 * @brief An ordered list of 4 floating-point numbers
 *
 * We use tuples to define other ray-tracer components, such as position and
 * vectors.
 *
 */
class Tuple
{
public:
    /**
     * @brief The number of components in a tuple
     *
     */
    static constexpr std::size_t SIZE = 4;

    /**
     * @brief Construct a zero-initialized tuple
     *
     */
    Tuple() = default;

    /**
     * @brief Construct a user-initialized tuple
     *
     * @param x The x component
     * @param y The y component
     * @param z The z component
     * @param w The w component
     */
    Tuple(double x, double y, double z, double w);

    /**
     * @brief Construct a tuple from an array of values
     *
     * @param init_values The array of initial values
     */
    Tuple(const std::array<double, Tuple::SIZE> &init_values);

    /**
     * @brief Get the x component, by const reference
     *
     * @return const double&
     */
    const double &x() const;

    /**
     * @brief Get the x component, by reference
     *
     * @return double Component value
     */
    double &x();

    /**
     * @brief Get the y component, by const reference
     *
     * @return double Component value
     */
    const double &y() const;

    /**
     * @brief Get the y component, by reference
     *
     * @return double Component value
     */
    double &y();

    /**
     * @brief Get the z component, by const reference
     *
     * @return double Component value
     */
    const double &z() const;

    /**
     * @brief Get the z component, by reference
     *
     * @return double Component value
     */
    double &z();

    /**
     * @brief Get the w component, by const reference
     *
     * @return double Component value
     */
    const double &w() const;

    /**
     * @brief Get the w component, by reference
     *
     * @return double Component value
     */
    double &w();

    /**
     * @brief Get an iterator to the beginning of the tuple's components
     *
     * @return const double*
     */
    const double *cbegin() const;

    /**
     * @brief Get an iterator to the beginning of the tuple's components
     *
     * @return double*
     */
    double *begin();

    /**
     * @brief Get an iterator to one past the end of the tuple's components
     *
     * @return const double*
     */
    const double *cend() const;

    /**
     * @brief Get an iterator to one past the end of the tuple's components
     *
     * @return double*
     */
    double *end();

private:
    ////////////////////////
    /// Member Variables ///
    ////////////////////////

    /**
     * @brief An array containing the tuple's components
     *
     */
    std::array<double, Tuple::SIZE> components{};
};

/**
 * @brief Overload the == operator
 *
 * Check two tuples for component-wise equality.
 *
 * @param lhs The left-hand side tuple
 * @param rhs The right-hand side tuple
 * @return true If all corresponding components are equal
 * @return false If any corresponding components are not equal
 */
bool operator==(const Tuple &lhs, const Tuple &rhs);

/**
 * @brief Overload the unary - operator
 *
 * Negate a tuple by inverting each component.
 *
 * @param tuple The tuple being negated
 * @return Tuple& Result of negation
 */
Tuple operator-(const Tuple &tuple);

/**
 * @brief Overload the + operator
 *
 * Creates a new tuple whose components are the sum of the corresponding
 * operand components.
 *
 * @param lhs The left-hand side tuple
 * @param rhs The right-hand side tuple
 * @return Tuple Result of the component-wise sum
 */
Tuple operator+(const Tuple &lhs, const Tuple &rhs);

/**
 * @brief Overload the - operator
 *
 * @param lhs The left-hand side tuple
 * @param rhs The right-hand side tuple
 * @return Tuple Result of the component-wise subtraction
 */
Tuple operator-(const Tuple &lhs, const Tuple &rhs);

/**
 * @brief Overload the * operator for scaling
 *
 * Scale a tuple by multiplying each component by the scalar value.
 *
 * @param tuple Tuple to be scaled
 * @param scalar Scalar value to be applied
 * @return Tuple& Resulting scaled tuple
 */
Tuple operator*(const Tuple &tuple, double scalar);

/**
 * @brief Overload the * operator for scaling
 *
 * Scale a tuple by multiplying each component by the scalar value.
 *
 * @param scalar Scalar value to be applied
 * @param tuple Tuple to be scaled
 * @return Tuple& Resulting scaled tuple
 */
Tuple operator*(double scalar, const Tuple &tuple);

/**
 * @brief Overload the / operator for scaling
 *
 * Scalar division divides each tuple element by the scalar value.
 *
 * @param tuple Tuple to be divided
 * @param divisor Scalar value for division
 * @return Tuple& Resulting scaled tuple
 */
Tuple operator/(const Tuple &tuple, double divisor);

/**
 * @brief Calculate the dot or inner product of two tuples
 *
 * @param lhs The left-hand side tuple
 * @param rhs The right-hand side tuple
 * @return double Result of the dot product calculation
 */
double dot(const Tuple &lhs, const Tuple &rhs);
