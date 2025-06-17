#include <cmath>
#include <Math/Sphere.hpp>
#include <Math/Transformations.hpp>

Vector Sphere::normal_at(const Point &point) const
{
    Point object_point = inverse(transform) * point;
    Vector object_normal = object_point - Point(0, 0, 0);
    Tuple world_normal = transpose(inverse(transform)) * object_normal;
    world_normal.w() = 0;

    return normalize(world_normal);
}
std::vector<Intersection> Sphere::local_intersect(const Ray &ray) const
{
    auto sphere_to_ray = ray.origin - Point(0, 0, 0);

    auto a = dot(ray.direction, ray.direction);
    auto b = 2 * dot(ray.direction, sphere_to_ray);
    auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

    auto discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0)
    {
        return std::vector<Intersection>();
    }

    auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    return {Intersection{t1, this}, Intersection{t2, this}};
}
