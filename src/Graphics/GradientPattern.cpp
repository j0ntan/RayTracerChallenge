#include <Graphics/GradientPattern.hpp>

#include <cmath>

GradientPattern::GradientPattern(const Color &a, const Color &b) : a{a}, b{b}
{
}

std::unique_ptr<Pattern> GradientPattern::clone() const
{
    return std::make_unique<GradientPattern>(*this);
}

Color GradientPattern::pattern_at(const Point &point) const
{
    auto distance = b - a;
    auto fraction = point.x() - std::floor(point.x());

    return a + distance * fraction;
}
