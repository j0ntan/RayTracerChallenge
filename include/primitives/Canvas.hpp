#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Color.hpp"
#include <vector>

class Canvas {
public:
  Canvas(const unsigned int width, const unsigned int height);

  Color pixel(const unsigned int x, const unsigned int y) const;
  void write(const unsigned int x, const unsigned int y, const Color &color);

  const unsigned int width, height;

private:
  std::vector<std::vector<Color>> pixels;
};

#endif
