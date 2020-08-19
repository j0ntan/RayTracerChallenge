#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

class Vector {
public:
  Vector();
  Vector(double x, double y, double z);

  bool operator==(const Vector &rhs) const;

  double magnitude() const;
  Vector normalize() const;

  double x;
  double y;
  double z;
};

Point operator+(const Vector &lhs, const Point &rhs);
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

#endif
