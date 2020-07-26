#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

class Vector {
public:
  Vector();
  Vector(double x, double y, double z);

  bool operator==(const Vector &rhs) const;

  Vector operator+(const Vector &rhs) const;
  Point operator+(const Point &rhs) const;

  double x;
  double y;
  double z;
};

Point operator+(const Point &lhs, const Vector &rhs);
Vector operator-(const Point &lhs, const Point &rhs);

#endif
