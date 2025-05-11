#include <stdexcept>
#include <Float_compare.hpp>
#include <Math/Point.hpp>

Point::Point() : Tuple{0, 0, 0, 1}
{
}

Point::Point(double x, double y, double z) : Tuple{x, y, z, 1}
{
}

Point::Point(const Tuple &tuple) : Tuple{tuple}
{
    if (!float_equals(tuple.w(), 1))
        throw std::invalid_argument("Point invalid with Tuple::w not 1");
}

bool operator==(const Point &lhs, const Point &rhs)
{
    return static_cast<Tuple>(lhs) == static_cast<Tuple>(rhs);
}
