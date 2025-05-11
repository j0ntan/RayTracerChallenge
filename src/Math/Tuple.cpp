#include <algorithm>
#include <functional>
#include <numeric>
#include <Float_compare.hpp>
#include <Math/Tuple.hpp>

Tuple::Tuple(double x, double y, double z, double w) : components{x, y, z, w}
{
}

Tuple::Tuple(const std::array<double, Tuple::SIZE> &init_values)
    : components{init_values}
{
}

const double &Tuple::x() const
{
    return components[0];
}

double &Tuple::x()
{
    return components[0];
}

const double &Tuple::y() const
{
    return components[1];
}

double &Tuple::y()
{
    return components[1];
}

const double &Tuple::z() const
{
    return components[2];
}

double &Tuple::z()
{
    return components[2];
}

const double &Tuple::w() const
{
    return components[3];
}

double &Tuple::w()
{
    return components[3];
}

const double *Tuple::cbegin() const
{
    return components.cbegin();
}

double *Tuple::begin()
{
    return components.begin();
}

const double *Tuple::cend() const
{
    return components.cend();
}

double *Tuple::end()
{
    return components.end();
}

bool operator==(const Tuple &lhs, const Tuple &rhs)
{
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), float_equals);
}

Tuple operator-(const Tuple &tuple)
{
    Tuple negated;
    std::transform(tuple.cbegin(), tuple.cend(), negated.begin(),
                   std::negate<double>());
    return negated;
}

Tuple operator+(const Tuple &lhs, const Tuple &rhs)
{
    Tuple sum;
    std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), sum.begin(),
                   std::plus<double>());
    return sum;
}

Tuple operator-(const Tuple &lhs, const Tuple &rhs)
{
    Tuple difference;
    std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), difference.begin(),
                   std::minus<double>());
    return difference;
}

Tuple operator*(const Tuple &tuple, double scalar)
{
    Tuple scaled;
    std::transform(tuple.cbegin(), tuple.cend(), scaled.begin(),
                   std::bind(std::multiplies<double>(),
                             std::placeholders::_1, scalar));
    return scaled;
}

Tuple operator*(double scalar, const Tuple &tuple)
{
    return tuple * scalar;
}

Tuple operator/(const Tuple &tuple, double divisor)
{
    Tuple divided;
    std::transform(tuple.cbegin(), tuple.cend(), divided.begin(),
                   std::bind(std::divides<double>(),
                             std::placeholders::_1, divisor));
    return divided;
}

double dot(const Tuple &lhs, const Tuple &rhs)
{
    return std::inner_product(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 0.0);
}
