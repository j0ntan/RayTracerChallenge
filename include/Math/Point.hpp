#pragma once

#include <Math/Tuple.hpp>

/**
 * @brief A point in the ray tracer 3D world-space
 *
 * A point object holds the x, y & z components of a point in the ray tracer
 * coordinate system. The fourth component, w = 1, helps to differentiate a
 * point from a vector, since they are both 4-element tuples.
 *
 */
class Point : public Tuple
{
public:
    /**
     * @brief Construct a zero-initialized point
     *
     */
    Point();

    /**
     * @brief Construct a new point object with initial component values
     *
     * @param x,y,z Initial values
     */
    Point(double x, double y, double z);

    /**
     * @brief Construct a new point object with a tuple initializer
     *
     * @param tuple Tuple with initial values
     */
    Point(const Tuple &tuple);

private:
    // make inaccessible from the Point interface
    using Tuple::w;
};

/**
 * @brief Overload the == operator; check equality of x,y,z values
 *
 * @param lhs The left-hand side point
 * @param rhs The right-hand side point
 * @return true If all corresponding components are equal
 * @return false If any corresponding components are not equal
 */
bool operator==(const Point &lhs, const Point &rhs);
