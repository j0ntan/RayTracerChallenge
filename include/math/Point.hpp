#ifndef POINT_HPP
#define POINT_HPP

#include "Tuple.hpp"

struct Point final : public Tuple<3> {
  Point();
  Point(double x, double y, double z);
  explicit Point(const Tuple<3> &values);

  Point &operator=(const Point &rhs);

  double &x = elements[0];
  double &y = elements[1];
  double &z = elements[2];
};

#endif
