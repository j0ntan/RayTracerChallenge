#include <cmath>
#include <math/Intersections.hpp>

std::vector<double> intersect(const Sphere &sphere, const Ray &ray) {
  std::vector<double> result;

  const auto sphere_to_ray = ray.origin - Point(0, 0, 0);

  const auto a = dot(ray.direction, ray.direction);
  const auto b = 2 * dot(ray.direction, sphere_to_ray);
  const auto c = dot(sphere_to_ray, sphere_to_ray) - 1;
  const auto discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    const auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    const auto t2 = (-b + sqrt(discriminant)) / (2 * a);
    result.push_back(t1);
    result.push_back(t2);
  }

  return result;
}
