#include <Graphics/CheckerPattern.hpp>

#include <cmath>

CheckerPattern::CheckerPattern(const Color &a, const Color &b) : a{a}, b{b}
{
}

std::unique_ptr<Pattern> CheckerPattern::clone() const
{
    return std::make_unique<CheckerPattern>(*this);
}

Color CheckerPattern::pattern_at(const Point &point) const
{
    auto sum = static_cast<int>(std::floor(point.x()) + std::floor(point.y()) +
                                std::floor(point.z()));

    return (sum % 2 == 0) ? a : b;
}
