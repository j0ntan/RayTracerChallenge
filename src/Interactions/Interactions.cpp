#include <cmath>
#include <algorithm>
#include <Interactions.hpp>

std::vector<Intersection>
intersections(const std::vector<Intersection> &set)
{
    std::vector<Intersection> sorted(set);
    std::sort(sorted.begin(), sorted.end(),
              [=](auto i1, auto i2)
              { return i1.t < i2.t; });
    return sorted;
}

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray)
{
    auto transformed_ray = transform(ray, inverse(sphere.transform));

    auto sphere_to_ray = transformed_ray.origin - Point(0, 0, 0);

    auto a = dot(transformed_ray.direction, transformed_ray.direction);
    auto b = 2 * dot(transformed_ray.direction, sphere_to_ray);
    auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

    auto discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0)
    {
        return std::vector<Intersection>();
    }

    auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    return {Intersection{t1, &sphere}, Intersection{t2, &sphere}};
}

std::optional<Intersection> hit(const std::vector<Intersection> &intersections)
{
    auto positive_hit_it =
        std::find_if(intersections.cbegin(), intersections.cend(),
                     [&](auto intersection)
                     { return intersection.t > 0; });

    return (positive_hit_it == intersections.end())
               ? std::nullopt
               : std::make_optional(*positive_hit_it);
}
