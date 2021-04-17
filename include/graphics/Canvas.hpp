#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Color.hpp"
#include <ostream>
#include <vector>

class Canvas {
public:
  Canvas(size_t width, size_t height);

  Color pixel(size_t x, size_t y) const;
  void write(size_t x, size_t y, const Color &color);

  void to_ppm(std::ostream &out) const;
  void to_ppm_file(const char *filename) const;

  const size_t width, height;

private:
  std::vector<std::vector<Color>> pixels;
};

#endif
