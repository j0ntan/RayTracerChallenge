#include <math/Ray.hpp>

Ray::Ray(const Point &origin, const Vector &direction)
    : origin{origin}, direction{direction} {}

Point position(const Ray &ray, const double t) {
  return ray.origin + ray.direction * t;
}
