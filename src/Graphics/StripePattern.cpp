#include <Graphics/StripePattern.hpp>

#include <cmath>
#include <Math/Shape.hpp>

Color StripePattern::stripe_at(const Point &point) const
{
    return ((static_cast<int>(std::floor(point.x())) % 2) == 0) ? a : b;
}

Color StripePattern::stripe_at_object(const Shape &object,
                                      const Point &world_point) const
{
    auto object_point = inverse(object.transform) * world_point;
    auto pattern_point = inverse(transform) * object_point;

    return stripe_at(pattern_point);
}
