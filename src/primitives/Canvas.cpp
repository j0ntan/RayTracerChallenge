#include <primitives/Canvas.hpp>

Canvas::Canvas(const unsigned int width, const unsigned int height)
    : width{width}, height{height} {}

Color Canvas::pixel(const unsigned int x, const unsigned int y) const {
  return Color();
}
