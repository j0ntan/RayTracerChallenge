#pragma once

#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Vector.hpp>

/**
 * @brief Represents light rays that are cast to produce our images
 *
 */
struct Ray {
  /**
   * @brief Construct a new Ray object
   *
   * @param origin The ray's origin
   * @param direction The ray's direction
   */
  explicit Ray(const Point &origin, const Vector &direction);

  /**
   * @brief The ray's point of origin in world-space
   *
   */
  const Point ORIGIN;

  /**
   * @brief The ray's velocity vector in world-space
   *
   */
  const Vector DIRECTION;
};

/**
 * @brief Create a new ray whose origin & direction vector are transformed by
 * the given matrix
 *
 * This function essentially converts a `Ray` in world-space to object-space,
 * based on the transformation given by a transformed object or shape. This new
 * ray is used to calculate the intersections to the object.
 *
 * @param ray The given ray in world-space
 * @param m The object's transformation matrix
 * @return Ray The new ray in object-space
 */
Ray transform(const Ray &ray, const Matrix<4> &m);

/**
 * @brief Compute the `Point` at the given distance `t` along the ray
 *
 * @param ray Incident ray
 * @param t The distance (time) value, in seconds
 * @return Point The point along the ray
 */
Point position(const Ray &ray, const double t);
