#include <Math/Shape.hpp>

Vector Shape::normal_at(const Point &point) const
{
    auto local_point = inverse(transform) * point;
    auto local_normal = this->local_normal_at(local_point);
    auto world_normal = transpose(inverse(transform)) * local_normal;
    world_normal.w() = 0;

    return normalize(world_normal);
}

Color Shape::pattern_at(const Point &world_point) const
{
    auto object_point = inverse(transform) * world_point;
    auto pattern_point = inverse(material.pattern->transform) * object_point;

    return material.pattern->pattern_at(pattern_point);
}
