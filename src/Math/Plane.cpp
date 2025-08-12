#include <cmath>
#include <Float_compare.hpp>
#include <Math/Plane.hpp>

Vector Plane::local_normal_at(const Point &point) const
{
    return Vector(0, 1, 0);
}

std::vector<Intersection> Plane::local_intersect(const Ray &ray) const
{
    std::vector<Intersection> intersections;

    if (std::abs(ray.direction.y()) >= EPSILON)
    {
        auto t = -ray.origin.y() / ray.direction.y();
        intersections.emplace_back(Intersection{.t = t, .object = this});
    }

    return intersections;
}
