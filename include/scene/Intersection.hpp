#pragma once

#include <optional>
#include <vector>

// forward declare for `Intersection` pointer member
class Sphere;

/**
 * @brief
 *
 */
class Intersection {
public:
  /**
   * @brief Construct a new Intersection object
   *
   * @param time
   * @param sphere
   */
  Intersection(double time, const Sphere &sphere);

  /**
   * @brief
   *
   * @return double
   */
  double time() const;

  /**
   * @brief
   *
   * @return const Sphere&
   */
  const Sphere &object() const;

private:
  /**
   * @brief
   *
   */
  double time_;

  /**
   * @brief
   *
   */
  const Sphere *object_;
};

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator==(const Intersection &lhs, const Intersection &rhs);

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator!=(const Intersection &lhs, const Intersection &rhs);

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator<(const Intersection &lhs, const Intersection &rhs);

/**
 * @brief
 *
 * @param intersections
 * @return std::optional<Intersection>
 */
std::optional<Intersection> hit(std::vector<Intersection> intersections);
