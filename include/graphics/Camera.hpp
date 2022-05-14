#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <graphics/Canvas.hpp>
#include <math/Matrix.hpp>
#include <scene/Ray.hpp>
#include <scene/World.hpp>

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

Ray ray_for_pixel(const Camera &camera, std::size_t x, std::size_t y);
Canvas render(const Camera &camera, const World &world);

#endif
