#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

class Sphere {
public:
  Sphere();
  explicit Sphere(const double radius, const Point &origin);

  double radius() const;
  Point origin() const;

private:
  const double r;
  const Point origin_;
};

#endif
