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

Ray ray_for_pixel(const Camera &camera, std::size_t x, std::size_t y) {
  // the offset from the edge of the canvas to the pixel's center
  auto xoffset = (x + 0.5) * camera.pixel_size;
  auto yoffset = (y + 0.5) * camera.pixel_size;

  // the untransformed coordinates of the pixel in world space
  auto world_x = camera.half_width - xoffset;
  auto world_y = camera.half_height - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // then compute the ray's direction vector
  auto pixel = Point(inverse(camera.transform) * Point{world_x, world_y, -1});
  auto origin = Point(inverse(camera.transform) * Point{0, 0, 0});
  auto direction = (pixel - origin).normalize();

  return Ray(origin, direction);
}

Canvas render(const Camera &camera, const World &world) {
  Canvas image(camera.hsize, camera.vsize);

  for (std::size_t y = 0; y < camera.vsize; ++y)
    for (std::size_t x = 0; x < camera.hsize; ++x) {
      auto ray = ray_for_pixel(camera, x, y);
      auto color = color_at(world, ray);
      image.write(x, y, color);
    }

  return image;
}
