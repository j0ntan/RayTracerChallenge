#include <math/Transformations.hpp>
#include <scene/Sphere.hpp>

Shape::Shape() : material{Material()} {}

Shape::Shape(Material material) : material{material} {}

Matrix<4> Shape::transformation() const { return transformation_; }

void Shape::apply_transformation(const Matrix<4> &new_transformation) {
  transformation_ = new_transformation;
}

Sphere::Sphere(Material material) : Shape{material} {}

Vector Sphere::normal_at(const Point &point) const {
  auto object_point = Point(inverse(transformation_) * point);
  auto object_normal = Vector(object_point - ORIGIN);
  auto world_normal =
      Vector(transpose(inverse(transformation_)) * object_normal);
  world_normal[3] = 0;
  return world_normal.normalize();
}
