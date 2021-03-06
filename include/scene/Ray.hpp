#ifndef RAY_HPP
#define RAY_HPP

#include <math/Point.hpp>
#include <math/Vector.hpp>

struct Ray {
  explicit Ray(const Point &origin, const Vector &direction);

  const Point origin;
  const Vector direction;
};

Point position(const Ray &ray, const double t);

#endif
