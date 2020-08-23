#include <cmath>
#include <utility/Float_compare.hpp>

namespace {
const double EPSILON =
    0.0001; // Min. allowed difference of two equal floating-point numbers
} // namespace

bool float_equals(const double number1, const double number2) {
  return std::abs(number2 - number1) <= EPSILON;
}
