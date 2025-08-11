#include <Math/Shape.hpp>

Vector Shape::normal_at(const Point &point) const
{
    auto local_point = inverse(transform) * point;
    auto local_normal = this->local_normal_at(local_point);
    auto world_normal = transpose(inverse(transform)) * local_normal;
    world_normal.w() = 0;

    return normalize(world_normal);
}
