#pragma once

/**
 * @brief Compare 2 floating-point numbers for equality
 *
 * @param number1 First number compared
 * @param number2 Second number compared
 * @return true The difference is less than or equal to `EPSILON`
 * @return false The difference is more than `EPSILON`
 */
bool float_equals(double number1, double number2);
