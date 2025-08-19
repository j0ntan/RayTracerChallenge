#include <StripePattern.hpp>
#include <cmath>

Color StripePattern::stripe_at(const Point &point) const
{
    return ((static_cast<int>(std::floor(point.x())) % 2) == 0) ? a : b;
}
