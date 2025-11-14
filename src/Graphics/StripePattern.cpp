#include <Graphics/StripePattern.hpp>

#include <cmath>

StripePattern::StripePattern(const Color &a, const Color &b) : a{a}, b{b}
{
}

std::unique_ptr<Pattern> StripePattern::clone() const
{
    return std::make_unique<StripePattern>(*this);
}

Color StripePattern::pattern_at(const Point &point) const
{
    return ((static_cast<int>(std::floor(point.x())) % 2) == 0) ? a : b;
}
