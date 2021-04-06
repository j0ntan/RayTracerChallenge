#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstddef>

struct Pixel {
  Pixel();
  Pixel(size_t R, size_t G, size_t B);

  const std::byte red;
  const std::byte green;
  const std::byte blue;
};

#endif
