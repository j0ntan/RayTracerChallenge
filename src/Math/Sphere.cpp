#include <Math/Sphere.hpp>

Vector Sphere::normal_at(const Point &point) const
{
    Point object_point = inverse(transform) * point;
    Vector object_normal = object_point - Point(0, 0, 0);
    Tuple world_normal = transpose(inverse(transform)) * object_normal;
    world_normal.w() = 0;

    return normalize(world_normal);
}
