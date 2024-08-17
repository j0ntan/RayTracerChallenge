#pragma once

#include <cmath>

#include "Point.hpp"
#include "Tuple.hpp"

///
/// @brief Function declarations for operators on `Point` and `Vector` objects,
/// defined further below.
///
class Vector;
Point operator+(const Point &lhs, const Vector &rhs);
Point operator-(const Point &lhs, const Vector &rhs);
Vector operator+(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &vector);
Vector operator-(const Point &lhs, const Point &rhs);
Vector operator-(const Vector &lhs, const Vector &rhs);
Vector operator*(const Vector &lhs, double rhs);
Vector operator*(double lhs, const Vector &rhs);
Vector operator/(const Vector &lhs, double rhs);
double dot(const Vector &lhs, const Vector &rhs);
Vector cross(const Vector &lhs, const Vector &rhs);
Vector reflect(const Vector &incident, const Vector &normal);
///
///
///

/**
 * @brief Generic 3D vector for the ray tracer world-space

 * A `Vector` holds `x`,`y` & `z` components. The fourth component, `w` = 0,
 * helps to differentiate a Vector from a Point, since they are both 4-element
 * Tuples.
 *
 */
struct Vector final : public Tuple<4> {

  /**
   * @brief Construct a new Vector object as a null vector
   *
   */
  Vector() = default;

  /**
   * @brief Construct a new Vector object with given initial values
   *
   * @param x, y, z Initial values
   */
  Vector(double x, double y, double z);

  /**
   * @brief Construct a new Vector object with a Tuple containing initial values
   *
   * @param values Initial values
   */
  explicit Vector(const Tuple<3> &values);

  /**
   * @brief Construct a new Vector object with a Tuple containing initial values
   *
   * @param values Initial values
   */
  explicit Vector(const Tuple<4> &values);

  /**
   * @brief Overload for the assignment operator by default assignment
   *
   * @param rhs The `Vector` whose values are assigned to the caller
   * @return Vector& Returns the caller after assignment
   */
  Vector &operator=(const Vector &rhs) = default;

  /**
   * @brief Calculate the magnitude or length of the calling `Vector`
   *
   * @return double The magnitude value
   */
  double magnitude() const;

  /**
   * @brief Create a unit vector for the calling `Vector`
   *
   * @return Vector The resulting unit vector
   */
  Vector normalize() const;

  /**
   * @brief Accessor functions for each `Vector` component
   *
   * @return double&, double The accessed component returned by reference or by
   * value, respectively
   */
  double &x();
  double &y();
  double &z();
  double x() const;
  double y() const;
  double z() const;
};

/**
 * @brief Overload the + operator for a `Point` & `Vector`
 *
 * Create a `Point` using the element-wise sum of two other `Tuple` objects. The
 * new `Point` is effectively the result of "moving" the given `point` to
 * another location in world-space determined by the `displacement` `Vector`.
 *
 * @param displacement Left-hand side operand
 * @param point Right-hand side operand
 * @return Point The displaced point in world-space
 */
Point operator+(const Vector &displacement, const Point &point);

/**
 * @brief Overload the + operator for a `Point` & `Vector`
 *
 * Call the other overloaded + operator with the operands swapped.

 * Create a `Point` using the element-wise sum of two other `Tuple` objects. The
 * new `Point` is effectively the result of "moving" the given `point` to
 * another location in world-space determined by the `displacement` `Vector`.
 *
 * @param point The source point
 * @param displacement The displacement vector
 * @return Point The displaced point in world-space
 */
Point operator+(const Point &point, const Vector &displacement);

/**
 * @brief Overload the - operator for a `Point` & `Vector`
 *
 * Create a `Point` using the element-wise subtraction of two other `Tuple`
 * objects. The new `Point` is effectively the result of "moving" the given
 * `point` to another location in world-space determined by the `displacement`
 * `Vector`. The `point` is "moved" in the reverse direction of the
 * `displacement` `Vector`.
 *
 * @param point The source point
 * @param displacement The displacement vector
 * @return Point The displaced point in world-space
 */
Point operator-(const Point &point, const Vector &displacement);

/**
 * @brief Overload the + operator for two `Vector` objects
 *
 * Create a `Vector` using the element-wise sum of two other `Vector` objects.
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Vector Result of the element-wise sum
 */
Vector operator+(const Vector &lhs, const Vector &rhs);

/**
 * @brief Overload the unary - operator for a `Vector`
 *
 * Negate a `Vector` by changing the sign of each element. This creates a
 * `Vector` that points in the opposite direction of the calling object.
 *
 * @param vector Source vector
 * @return Vector Negated vector
 */
Vector operator-(const Vector &vector);

/**
 * @brief Overload the - operator  for two `Point` objects
 *
 * Create a `Vector` using the element-wise subtraction of two `Point` objects.
 * The resulting `Vector` will point from `p2` to `p1`, given that it was
 * created from the expression `p1` - `p2`.
 *
 * @param p1
 * @param p2
 * @return Vector A displacement vector between two given points
 */
Vector operator-(const Point &p1, const Point &p2);

/**
 * @brief Overload the - operator for two `Vector` objects
 *
 * Create a `Vector` using the element-wise subtraction of two `Vector` objects.
 * The resulting vector represents the change in direction between the two
 * operands.
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Vector Result of the element-wise subtraction
 */
Vector operator-(const Vector &lhs, const Vector &rhs);

/**
 * @brief Overload the * operator for scaling
 *
 * Scale the given `vector` by multiplying each element by the `scalar` value,
 * changing its length.
 *
 * @param vector Vector to be scaled
 * @param scalar Scalar value to be applied
 * @return Vector Resulting scaled vector
 */
Vector operator*(const Vector &vector, double scalar);

/**
 * @brief Overload the * operator for scaling
 *
 * Scale the given `vector` by multiplying each element by the `scalar` value,
 * changing its length.
 *
 * @param scalar Scalar value to be applied
 * @param vector Vector to be scaled
 * @return Vector Resulting scaled vector
 */
Vector operator*(double scalar, const Vector &vector);

/**
 * @brief Overload the / operator for scaling
 *
 * Scalar division divides each `vector` element by the `scalar` value.
 *
 * @param vector Vector to be divided
 * @param scalar Scalar value for division
 * @return Vector Resulting scaled vector
 */
Vector operator/(const Vector &vector, double scalar);

/**
 * @brief Calculate the dot or inner product of two `Vector` objects
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return double Result of the dot product calculation
 */
double dot(const Vector &lhs, const Vector &rhs);

/**
 * @brief Calculate the cross product of two `Vector` objects
 *
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return Vector Result vector of the cross product calculation
 */
Vector cross(const Vector &lhs, const Vector &rhs);

/**
 * @brief Create a ray's reflection vector from a given surface
 *
 * The reflection `Vector` is calculated from the given `incident` vector
 * interacting with the given `normal` vector of a surface in world-space.
 *
 * @param incident Vector of the incident ray
 * @param normal Normal vector for a point on a surface
 * @return Vector Reflection vector
 */
Vector reflect(const Vector &incident, const Vector &normal);
