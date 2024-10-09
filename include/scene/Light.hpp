#pragma once

#include <graphics/Color.hpp>
#include <math/Point.hpp>

/**
 * @brief This class represent a point light source in world-space
 *
 */
class Light {
public:
  /**
   * @brief Construct a new Light object
   *
   * @param position
   * @param intensity
   */
  Light(const Point &position, const Color &intensity);

  /**
   * @brief
   *
   */
  const Point POSITION;

  /**
   * @brief
   *
   */
  const Color INTENSITY;
};
