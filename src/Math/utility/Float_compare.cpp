#include <cmath>
#include <Float_compare.hpp>

bool float_equals(double number1, double number2)
{
    return std::islessequal(std::abs(number2 - number1), EPSILON);
}
