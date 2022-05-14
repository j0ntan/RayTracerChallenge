#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math/Matrix.hpp>

struct Camera {
  std::size_t hsize;
  std::size_t vsize;
  double field_of_view;
  Matrix<4> transform = identity;
};

#endif
