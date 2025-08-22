#include <Graphics/StripePattern.hpp>
#include <cmath>

Color StripePattern::stripe_at(const Point &point) const
{
    return ((static_cast<int>(std::floor(point.x())) % 2) == 0) ? a : b;
}

Color stripe_at_object(const StripePattern &pattern, const Sphere &object,
                       const Point &point)
{
    return Color();
}
