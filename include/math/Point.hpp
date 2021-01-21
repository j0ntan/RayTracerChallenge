#ifndef POINT_HPP
#define POINT_HPP

#include "Tuple.hpp"

struct Point final : public Tuple<3> {
  Point();
  Point(double x, double y, double z);
  explicit Point(const Tuple<3> &values);

  Point &operator=(const Point &rhs);

  double &x();
  double &y();
  double &z();
  double x() const;
  double y() const;
  double z() const;
};

#endif
