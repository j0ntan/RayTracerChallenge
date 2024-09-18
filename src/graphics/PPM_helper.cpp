#include <cmath>

#include "PPM_helper.hpp"

/**
 * @brief We only use RGB color values in the range [0. 255]
 *
 */
constexpr std::size_t MAX_COLOR = 255;

/**
 * @brief The PPM file should contain lines that are 70 chars long or less
 *
 */
constexpr std::size_t MAX_LINE_LEN = 70;

std::string write_header(const Canvas &canvas) {
  // Specify 'ASCII mode' for the PPM file, instead of 'binary mode'
  const std::string MAGIC_NUMBER_STR = "P3\n";

  const std::string SIZE_STR =
      std::to_string(canvas.width) + " " + std::to_string(canvas.height) + '\n';

  const std::string COLOR_STR = std::to_string(MAX_COLOR) + '\n';

  return MAGIC_NUMBER_STR + SIZE_STR + COLOR_STR;
}

std::string to_string(const Color &color) {
  // clamp the color values within [0.0, 1.0]
  Color clamped;
  clamped.red() = std::max(color.red(), 0.0);
  clamped.red() = std::min(clamped.red(), 1.0);
  clamped.green() = std::max(color.green(), 0.0);
  clamped.green() = std::min(clamped.green(), 1.0);
  clamped.blue() = std::max(color.blue(), 0.0);
  clamped.blue() = std::min(clamped.blue(), 1.0);

  // scale by MAX_COLOR & convert to str equivalent
  const auto RED_STR =
      std::to_string(static_cast<int>(std::round(MAX_COLOR * clamped.red())));
  const auto GREEN_STR =
      std::to_string(static_cast<int>(std::round(MAX_COLOR * clamped.green())));
  const auto BLUE_STR =
      std::to_string(static_cast<int>(std::round(MAX_COLOR * clamped.blue())));

  return RED_STR + ' ' + GREEN_STR + ' ' + BLUE_STR;
}

std::string to_string(const Canvas &canvas) {
  std::string result;
  std::size_t line_len = 0;

  // (3 digits + 1 space) * 3 color components = 12 chars reserved per pixel
  result.reserve(canvas.width * canvas.height * 12);

  for (std::size_t row = 0; row < canvas.height; ++row) {
    for (std::size_t col = 0; col < canvas.width; ++col) {
      const auto COLOR_STR = to_string(canvas.pixel(col, row)) + ' ';

      if (line_len + COLOR_STR.length() <= MAX_LINE_LEN) {
        line_len += COLOR_STR.length();
      } else {
        result.back() = '\n';
        line_len = COLOR_STR.length();
      }

      result.append(COLOR_STR);
    }
  }

  // replace final space char with newline
  result.back() = '\n';

  return result;
}
