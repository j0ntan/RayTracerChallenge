#ifndef POINT_HPP
#define POINT_HPP

#include "Tuple.hpp"

struct Point final : public Tuple<4> {
  /**
   * @brief Construct a default Point object with zeroed values.
   */
  Point();

  /**
   * @brief Construct an fully defined Point object.
   *
   * @param x
   * @param y
   * @param z
   */
  Point(double x, double y, double z);

  explicit Point(const Tuple<3> &values);
  explicit Point(const Tuple<4> &values);

  Point &operator=(const Point &rhs);

  double &x();
  double &y();
  double &z();
  double x() const;
  double y() const;
  double z() const;
};

#endif
