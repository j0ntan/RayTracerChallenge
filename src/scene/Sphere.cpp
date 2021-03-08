#include <scene/Sphere.hpp>

Sphere::Sphere() : r{1.0}, origin_{Point(0, 0, 0)}, transform{identity} {}

Sphere::Sphere(const double radius, const Point &origin)
    : r{radius}, origin_{origin}, transform{identity} {}

double Sphere::radius() const { return r; }

Point Sphere::origin() const { return origin_; }

Vector Sphere::normal(const Point &point) const {
  auto object_point = Point(inverse(transform) * point);
  auto object_normal = Vector(object_point - origin_);
  auto world_normal = Vector(transpose(inverse(transform)) * object_normal);
  world_normal[3] = 0;
  return world_normal.normalize();
}

Matrix<4> Sphere::transformation() const { return transform; }

void Sphere::set_transformation(const Matrix<4> &m) { transform = m; }

Material Sphere::material() const { return Material(); }
