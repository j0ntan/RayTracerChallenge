#include <Graphics/RingPattern.hpp>

#include <cmath>

RingPattern::RingPattern(const Color &a, const Color &b) : a{a}, b{b}
{
}

std::unique_ptr<Pattern> RingPattern::clone() const
{
    return std::make_unique<RingPattern>(*this);
}

Color RingPattern::pattern_at(const Point &point) const
{
    auto p_x = point.x(), p_z = point.z();
    auto distance =
        static_cast<int>(std::floor(std::sqrt(p_x * p_x + p_z * p_z)));

    return (distance % 2 == 0) ? a : b;
}
