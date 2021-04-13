#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Color.hpp"
#include "PPM.hpp"
#include <vector>

class Canvas {
public:
  Canvas(size_t width, size_t height);

  Color pixel(size_t x, size_t y) const;
  void write(size_t x, size_t y, const Color &color);

  PPM to_PPM(const MagicIdentifier &id) const;
  void write_PPM(const char *filename, const MagicIdentifier &id) const;

  const size_t width, height;

private:
  std::vector<std::vector<Color>> pixels;
};

#endif
