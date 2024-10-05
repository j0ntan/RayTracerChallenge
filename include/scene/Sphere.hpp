#pragma once

#include <vector>

#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Intersection.hpp>
#include <scene/Material.hpp>
#include <scene/Ray.hpp>

/**
 * @brief
 *
 */
class Shape {
public:
  /**
   * @brief Construct a new Shape object
   *
   */
  Shape();

  /**
   * @brief Construct a new Shape object
   *
   * @param material
   */
  Shape(Material material);

  /**
   * @brief
   *
   * @param point
   * @return Vector
   */
  virtual Vector normal_at(const Point &point) const = 0;

  /**
   * @brief
   *
   * @return Matrix<4>
   */
  Matrix<4> transformation() const;

  /**
   * @brief Set the transformation object
   *
   * @param new_transformation
   */
  void apply_transformation(const Matrix<4> &new_transformation);

  virtual ~Shape() = default;

  /**
   * @brief
   *
   */
  const Point ORIGIN = Point(0, 0, 0);

  /**
   * @brief
   *
   */
  Material material;

protected:
  /**
   * @brief
   *
   */
  Matrix<4> transformation_ = IDENTITY;
};

/**
 * @brief
 *
 */
class Sphere final : public Shape {
public:
  /**
   * @brief Construct a new Sphere object
   *
   */
  Sphere() = default;

  /**
   * @brief Construct a new Sphere object
   *
   * @param material
   */
  Sphere(Material material);

  /**
   * @brief
   *
   * @param point
   * @return Vector
   */
  virtual Vector normal_at(const Point &point) const;

  /**
   * @brief
   *
   * @param ray
   * @return std::vector<Intersection>
   */
  std::vector<Intersection> intersect(const Ray &ray) const;

  /**
   * @brief
   *
   */
  const double RADIUS = 1;
};
