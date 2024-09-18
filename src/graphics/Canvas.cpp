#include <cmath>
#include <fstream>
#include <string>

#include <graphics/Canvas.hpp>

#include "PPM_helper.hpp"

Canvas::Canvas(std::size_t width, std::size_t height)
    : width{width}, height{height},
      pixels{std::vector<std::vector<Color>>(
          height, std::vector<Color>(width, Color()))} {}

Color Canvas::pixel(std::size_t x, std::size_t y) const { return pixels[y][x]; }

void Canvas::write(std::size_t x, std::size_t y, const Color &color) {
  pixels[y][x] = color;
}

void write_PPM(const Canvas &canvas, const std::string &FILENAME) {
  std::ofstream output_file(FILENAME + ".ppm");
  output_file << write_header(canvas) << to_string(canvas);
}
