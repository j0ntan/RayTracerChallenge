#pragma once

#include "Tuple.hpp"

/**
 * @brief A point in the ray tracer 3D world-space
 *
 * A `Point` holds `x`,`y` & `z` components. The fourth component, `w` = 1,
 * helps to differentiate a Point from a Vector, since they are both 4-element
 * Tuples.
 *
 */
struct Point final : public Tuple<4> {

  /**
   * @brief Construct a new Point object at the origin (0,0,0).
   *
   */
  Point();

  /**
   * @brief Construct a new Point object with given initial values
   *
   * @param x,y,z Initial values
   */
  Point(double x, double y, double z);

  /**
   * @brief Construct a new Point object with a Tuple containing initial values
   *
   * @param values Initial values
   */
  explicit Point(const Tuple<3> &values);

  /**
   * @brief Construct a new Point object with a Tuple containing initial values
   *
   * Note: The fourth value in the Tuple is ignored, since `w` is always 1.
   *
   * @param values Initial values
   */
  explicit Point(const Tuple<4> &values);

  /**
   * @brief Overload for the assignment operator by default assignment
   *
   * @param rhs The `Point` whose values are assigned to the caller
   * @return Point& Returns the caller after assignment
   */
  Point &operator=(const Point &rhs) = default;

  /**
   * @brief Accessor functions for each `Point` component
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
