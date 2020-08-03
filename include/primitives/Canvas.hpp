#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Color.hpp"

class Canvas {
public:
  Canvas(const unsigned int width, const unsigned int height);

  Color pixel(const unsigned int x, const unsigned int y) const;

  const unsigned int width, height;
};

#endif
