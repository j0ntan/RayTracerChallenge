#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"
#include <math/Matrix.hpp>

class Sphere {
public:
  Sphere();
  explicit Sphere(const double radius, const Point &origin);

  double radius() const;
  Point origin() const;
  Matrix<4> transformation() const;

  void set_transformation(const Matrix<4> &m);

private:
  const double r;
  const Point origin_;
  Matrix<4> transform;
};

#endif
