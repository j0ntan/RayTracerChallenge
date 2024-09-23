#ifndef RAY_HPP
#define RAY_HPP

#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Vector.hpp>

struct Ray {
  explicit Ray(const Point &origin, const Vector &direction);

  const Point origin;
  const Vector direction;
};

Ray transform(const Ray &ray, const Matrix<4> &m);

Point position(const Ray &ray, const double t);

#endif
