#pragma once

#include <graphics/Color.hpp>

/**
 * @brief
 *
 */
struct Material {
  Color color = Color(1, 1, 1);
  double ambient = 0.1;
  double diffuse = 0.9;
  double specular = 0.9;
  double shininess = 200;
};

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator==(const Material &lhs, const Material &rhs);

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator!=(const Material &lhs, const Material &rhs);
