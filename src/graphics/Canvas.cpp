#include <cmath>
#include <fstream>
#include <graphics/Canvas.hpp>
#include <string>

Canvas::Canvas(size_t width, size_t height)
    : width{width}, height{height}, pixels{std::vector<std::vector<Color>>(
                                        height,
                                        std::vector<Color>(width, Color()))} {}

Color Canvas::pixel(size_t x, size_t y) const { return pixels[y][x]; }

void Canvas::write(size_t x, size_t y, const Color &color) {
  pixels[y][x] = color;
}

PPM Canvas::to_PPM(const MagicIdentifier &id) const {
  PPM ppm(width, height, id);

  for (size_t row = 0; row < height; ++row)
    for (size_t col = 0; col < width; ++col)
      ppm.write(
          row, col,
          Pixel{static_cast<size_t>(ppm.max_color * pixels[row][col].red()),
                static_cast<size_t>(ppm.max_color * pixels[row][col].green()),
                static_cast<size_t>(ppm.max_color * pixels[row][col].blue())});

  return ppm;
}

void Canvas::write_PPM(const char *filename, const MagicIdentifier &id) const {
  const auto PPM = to_PPM(id);
  if (id == MagicIdentifier::ASCII) {
    std::ofstream output_file(std::string(filename) + ".ppm");
    output_file << std::string(PPM);
  } else {
    std::ofstream output_file(std::string(filename) + ".ppm",
                              std::ios_base::binary);
    for (const auto &BYTE : PPM.bytes())
      output_file.put(static_cast<char>(BYTE));
  }
}
