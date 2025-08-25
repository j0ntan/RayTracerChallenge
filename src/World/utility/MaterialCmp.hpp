#pragma once

#include <Float_compare.hpp>
#include <World/Material.hpp>

/**
 * @brief Overload the = operator for two materials
 *
 * @param lhs The left-hand side material
 * @param rhs The right-hand side material
 * @return true If all corresponding properties are equal
 * @return false If any corresponding properties are not equal
 */
bool operator==(const Material &lhs, const Material &rhs)
{
    return lhs.color == rhs.color && float_equals(lhs.ambient, rhs.ambient) &&
           float_equals(lhs.diffuse, rhs.diffuse) &&
           float_equals(lhs.specular, rhs.specular) &&
           float_equals(lhs.shininess, rhs.shininess);
}
