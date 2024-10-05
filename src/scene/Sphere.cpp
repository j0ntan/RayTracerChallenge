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

std::vector<Intersection> Sphere::intersect(const Ray &ray) const {
  std::vector<Intersection> result;

  auto transformed_ray = transform(ray, inverse(transformation_));
  const auto sphere_to_ray = transformed_ray.ORIGIN - Point(0, 0, 0);

  const auto a = dot(transformed_ray.DIRECTION, transformed_ray.DIRECTION);
  const auto b = 2 * dot(transformed_ray.DIRECTION, sphere_to_ray);
  const auto c = dot(sphere_to_ray, sphere_to_ray) - 1;
  const auto discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    const auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    const auto t2 = (-b + sqrt(discriminant)) / (2 * a);
    result.push_back(Intersection(t1, *this));
    result.push_back(Intersection(t2, *this));
  }

  return result;
}
