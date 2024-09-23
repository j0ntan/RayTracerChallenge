#include <scene/Ray.hpp>

Ray::Ray(const Point &origin, const Vector &direction)
    : origin{origin}, direction{direction} {}

Ray transform(const Ray &ray, const Matrix<4> &m) {
  return Ray(Point(m * ray.origin), Vector(m * ray.direction));
}

Point position(const Ray &ray, const double t) {
  return ray.origin + ray.direction * t;
}
