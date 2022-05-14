#include <cmath>
#include <graphics/Camera.hpp>

Camera::Camera(std::size_t hsize, std::size_t vsize, double field_of_view)
    : hsize{hsize}, vsize{vsize}, field_of_view{field_of_view}, transform{
                                                                    identity} {
  auto half_view = tan(field_of_view / 2);
  auto aspect = static_cast<double>(hsize) / vsize;

  if (aspect > 1 || hsize == vsize) {
    half_width = half_view;
    half_height = half_view / aspect;
  } else {
    half_width = half_view * aspect;
    half_height = half_view;
  }

  pixel_size = (half_width * 2) / hsize;
}
