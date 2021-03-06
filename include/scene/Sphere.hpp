#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Material.hpp>

class Sphere {
public:
  Sphere();
  explicit Sphere(const double radius, const Point &origin);

  double radius() const;
  Point origin() const;

  Vector normal(const Point &point) const;

  Matrix<4> transformation() const;

  void set_transformation(const Matrix<4> &m);

  Material material() const;

  void set_material(const Material &material);

private:
  const double r;
  const Point origin_;
  Matrix<4> transform;
  Material material_;
};

#endif
