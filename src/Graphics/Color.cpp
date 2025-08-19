#include <Graphics/Color.hpp>

const Color Color::BLACK(0, 0, 0);
const Color Color::WHITE(1, 1, 1);

Color::Color(double red, double green, double blue) : Tuple{red, green, blue, 0}
{
}

Color::Color(const Tuple &tuple) : Tuple{tuple}
{
}

double Color::red() const
{
    return x();
}

double Color::green() const
{
    return y();
}

double Color::blue() const
{
    return z();
}

bool operator==(const Color &lhs, const Color &rhs)
{
    return static_cast<Tuple>(lhs) == static_cast<Tuple>(rhs);
}

Color operator+(const Color &lhs, const Color &rhs)
{
    return Color(static_cast<Tuple>(lhs) + static_cast<Tuple>(rhs));
}

Color operator-(const Color &lhs, const Color &rhs)
{
    return Color(static_cast<Tuple>(lhs) - static_cast<Tuple>(rhs));
}

Color operator*(const Color &color, double scalar)
{
    return Color(static_cast<Tuple>(color) * scalar);
}

Color operator*(double scalar, const Color &color)
{
    return color * scalar;
}

Color operator*(const Color &lhs, const Color &rhs)
{
    return Color{lhs.red() * rhs.red(),
                 lhs.green() * rhs.green(),
                 lhs.blue() * rhs.blue()};
}
