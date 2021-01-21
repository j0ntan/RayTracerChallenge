#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"
#include "Tuple.hpp"

struct Vector final : public Tuple<3> {
  Vector();
  Vector(double x, double y, double z);
  explicit Vector(const Tuple<3> &values);

  Vector &operator=(const Vector &rhs);

  double magnitude() const;
  Vector normalize() const;

  double &x();
  double &y();
  double &z();
  double x() const;
  double y() const;
  double z() const;
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
