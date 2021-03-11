#ifndef FLOAT_COMPARE_HPP
#define FLOAT_COMPARE_HPP

/**
 * @brief Maximum relative error defined for floating-point numbers.
 */
const double EPSILON = 0.0001;

/**
 * @brief Compares two floating-point numbers for equality.
 *
 * @details Two floating-point numbers are considered equal if their
 * difference is less than or equal to the value defined as 'EPSILON'.
 *
 * @param number1 First number in comparison.
 * @param number2 Second number in comparison.
 */
bool float_equals(const double number1, const double number2);

#endif
