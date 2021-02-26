#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

class Sphere {
public:
  Sphere();
  explicit Sphere(const double radius, const Point &origin);

  double radius() const;

private:
  const double r;
};

#endif
