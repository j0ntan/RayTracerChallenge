#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstddef>
#include <string>

struct Pixel {
  Pixel();
  Pixel(size_t R, size_t G, size_t B);

  explicit operator std::string() const;

  std::byte red;
  std::byte green;
  std::byte blue;
};

#endif
