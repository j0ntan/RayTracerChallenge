#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math/Matrix.hpp>

struct Camera {
  Camera(std::size_t hsize, std::size_t vsize, double field_of_view);

  std::size_t hsize;
  std::size_t vsize;
  double field_of_view;
  Matrix<4> transform;
  double pixel_size;
  double half_width;
  double half_height;
};

#endif
