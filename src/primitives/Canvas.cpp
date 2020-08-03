#include <primitives/Canvas.hpp>

Canvas::Canvas(const unsigned int width, const unsigned int height)
    : width{width}, height{height}, pixels{std::vector<std::vector<Color>>(
                                        width, std::vector<Color>(height))} {}

Color Canvas::pixel(const unsigned int x, const unsigned int y) const {
  return pixels[x][y];
}

void Canvas::write(const unsigned int x, const unsigned int y,
                   const Color &color) {
  pixels[x][y] = color;
}
