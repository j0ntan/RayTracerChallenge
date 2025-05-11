#pragma once

#include <Math/Point.hpp>

/**
 * @brief A vector in the ray tracer 3D world-space
 *
 * A vector object holds the x, y & z components of a vector in the ray tracer
 * coordinate system. The fourth component, w = 0, helps to differentiate a
 * point from a vector, since they are both 4-element tuples.
 *
 */
struct Vector : public Tuple
{
public:
    /**
     * @brief Construct a zero-initialized vector
     *
     */
    Vector() = default;

    /**
     * @brief Construct a new vector object with initial component values
     *
     * @param x,y,z Initial values
     */
    Vector(double x, double y, double z);

    /**
     * @brief Construct a new vector object with a tuple initializer
     *
     * @param tuple Tuple with initial values
     */
    Vector(const Tuple &tuple);

private:
    using Tuple::w; // make inaccessible from the Vector interface
};

/**
 * @brief Overload the - operator for two points
 *
 * Create a vector using the component-wise subtraction of two points. The
 * resulting vector will point from p2 to p1.
 *
 * @param lhs The left-hand side point
 * @param rhs The right-hand side point
 * @return Vector The displacement vector between the two points
 */
Vector operator-(const Point &lhs, const Point &rhs);

/**
 * @brief Overload the == operator; check equality of x,y,z values
 *
 * @param lhs The left-hand side vector
 * @param rhs The right-hand side vector
 * @return true If all corresponding components are equal
 * @return false If any corresponding components are not equal
 */
bool operator==(const Vector &lhs, const Vector &rhs);

/**
 * @brief Overload the - operator for a point & vector
 *
 * The new point is effectively the result of "moving" the given
 * point to another location in world-space determined by the displacement
 * vector. The point is "moved" in the reverse direction of the
 * displacement vector.
 *
 * @param point The source point
 * @param displacement The displacement vector
 * @return Point The displaced point in world-space
 */
Point operator-(const Point &point, const Vector &displacement);

/**
 * @brief Overload the - operator for two vectors
 *
 * Create a vector using the component-wise subtraction of two vectors. The
 * resulting vector represents the change in direction between the two
 * operands.
 *
 * @param lhs The left-hand side vector
 * @param rhs The right-hand side vector
 * @return Vector Result of the component-wise subtraction
 */
Vector operator-(const Vector &lhs, const Vector &rhs);

/**
 * @brief Calculate the magnitude or length of a vector
 *
 * The value is calculated using the classical Pythagorean formula and the
 * vector components.
 *
 * @param vector The vector used to calculate the magnitude
 * @return double The magnitude value
 */
double magnitude(const Vector &vector);

/**
 * @brief Create a unit vector for a given input vector
 *
 * @param vector The vector used to create a unit vector
 * @return Vector The resulting unit vector
 */
Vector normalize(const Vector &vector);

/**
 * @brief Calculate the dot or inner product of two vectors
 *
 * @param lhs The left-hand side vector
 * @param rhs The right-hand side vector
 * @return double Result of the dot product calculation
 */
double dot(const Vector &lhs, const Vector &rhs);

/**
 * @brief Calculate the cross product of two vectors
 *
 * @param lhs The left-hand side vector
 * @param rhs The right-hand side vector
 * @return Vector Resulting vector of the cross product calculation
 */
Vector cross(const Vector &lhs, const Vector &rhs);
