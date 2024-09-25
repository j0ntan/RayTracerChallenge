#include <scene/Ray.hpp>

Ray::Ray(const Point &origin, const Vector &direction)
    : ORIGIN{origin}, DIRECTION{direction} {}

Ray transform(const Ray &ray, const Matrix<4> &m) {
  return Ray(Point(m * ray.ORIGIN), Vector(m * ray.DIRECTION));
}

Point position(const Ray &ray, const double t) {
  return ray.ORIGIN + ray.DIRECTION * t;
}
