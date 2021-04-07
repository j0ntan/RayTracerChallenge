#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstddef>

struct Pixel {
  Pixel();
  Pixel(size_t R, size_t G, size_t B);

  std::byte red;
  std::byte green;
  std::byte blue;
};

#endif
