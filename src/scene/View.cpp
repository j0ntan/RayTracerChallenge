#include <scene/Transformations.hpp>
#include <scene/View.hpp>

Matrix<4> view_transform(const Point &from, const Point &to, const Vector &up) {
  auto forward = (to - from).normalize();

  auto left = cross(forward, up.normalize());

  auto true_up = cross(left, forward);

  Matrix<4> orientation = {{left.x(), left.y(), left.z(), 0},
                           {true_up.x(), true_up.y(), true_up.z(), 0},
                           {-forward.x(), -forward.y(), -forward.z(), 0},
                           {0, 0, 0, 1}};

  return orientation * translate(-from.x(), -from.y(), -from.z());
}
