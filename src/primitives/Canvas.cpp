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

void Canvas::to_ppm(std::ostream &out) const {
  out << "P3\n"
      << std::to_string(width) << ' ' << std::to_string(height) << '\n'
      << "255\n";

  for (size_t y = 0; y < height; ++y)
    for (size_t x = 0; x < width; ++x) {
      const auto &color = pixels[x][y];
      const auto &r = color.red;
      const auto &g = color.green;
      const auto &b = color.blue;
      out << r << ' ' << g << ' ' << b;
      if (x == (width - 1))
        out << '\n';
      else
        out << ' ';
    }
}
