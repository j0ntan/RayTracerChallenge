#include <cmath>
#include <fstream>
#include <graphics/Canvas.hpp>
#include <string>

namespace {
int scale(double num) { return static_cast<unsigned>(std::round(num * 255)); }

const size_t MAX_PPM_LINE_LENGTH = 70;

char whitespace(const std::string &prev_str, const std::string &next_str,
                size_t &current_line_length, bool right_edge_blue_outputted) {
  if (!right_edge_blue_outputted &&
      (current_line_length + prev_str.length() + 1 + next_str.length() <=
       MAX_PPM_LINE_LENGTH)) {
    ++current_line_length;
    return ' ';
  }

  current_line_length = 0;
  return '\n';
}

size_t to_index(const unsigned int x, const unsigned int y,
                const unsigned int width) {
  return width * y + x;
}
} // namespace

Canvas::Canvas(const unsigned int width, const unsigned int height)
    : width{width}, height{height}, pixels{width * height} {}

Color Canvas::pixel(const unsigned int x, const unsigned int y) const {
  return pixels[to_index(x, y, width)];
}

void Canvas::write(const unsigned int x, const unsigned int y,
                   const Color &color) {
  pixels[to_index(x, y, width)] = color;
}

void Canvas::to_ppm(std::ostream &out) const {
  out << "P3\n"
      << std::to_string(width) << ' ' << std::to_string(height) << '\n'
      << "255\n";

  size_t current_line_length = 0;
  for (size_t y = 0; y < height; ++y)
    for (size_t x = 0; x < width; ++x) {
      const auto &color = pixels[to_index(x, y, width)];
      const auto RED_STR = std::to_string(scale(color.red()));
      const auto GREEN_STR = std::to_string(scale(color.green()));
      const auto BLUE_STR = std::to_string(scale(color.blue()));

      out << RED_STR;
      current_line_length += RED_STR.length();
      out << whitespace(RED_STR, GREEN_STR, current_line_length, false);

      out << GREEN_STR;
      current_line_length += GREEN_STR.length();
      out << whitespace(GREEN_STR, BLUE_STR, current_line_length, false);

      out << BLUE_STR;
      current_line_length += BLUE_STR.length();
      out << whitespace(BLUE_STR, "", current_line_length, x == (width - 1));
    }
}

void Canvas::to_ppm_file(const char *filename) const {
  std::ofstream output_file(std::string(filename) + ".ppm");
  to_ppm(output_file);
}
