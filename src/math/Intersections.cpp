#include <algorithm>
#include <cmath>
#include <math/Intersections.hpp>
#include <math/Transformations.hpp>

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray) {
  std::vector<Intersection> result;

  auto transformed_ray = transform(ray, inverse(sphere.transformation()));
  const auto sphere_to_ray = transformed_ray.origin - Point(0, 0, 0);

  const auto a = dot(transformed_ray.direction, transformed_ray.direction);
  const auto b = 2 * dot(transformed_ray.direction, sphere_to_ray);
  const auto c = dot(sphere_to_ray, sphere_to_ray) - 1;
  const auto discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    const auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    const auto t2 = (-b + sqrt(discriminant)) / (2 * a);
    result.push_back(Intersection(t1, sphere));
    result.push_back(Intersection(t2, sphere));
  }

  return result;
}

std::optional<Intersection> hit(std::vector<Intersection> intersections) {
  std::sort(intersections.begin(), intersections.end());

  for (const auto &i : intersections)
    if (i.time() >= 0)
      return std::make_optional(i);

  return std::nullopt;
}
