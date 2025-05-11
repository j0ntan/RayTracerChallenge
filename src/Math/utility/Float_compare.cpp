#include <cmath>
#include <Float_compare.hpp>

namespace
{
    /**
     * @brief Minimum allowed difference of two equal floating-point numbers
     *
     */
    const double EPSILON = 0.00001;
}

bool float_equals(double number1, double number2)
{
    return std::islessequal(std::abs(number2 - number1), EPSILON);
}
