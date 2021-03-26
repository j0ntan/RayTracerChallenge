#ifndef PPM_H
#define PPM_H

#include <cstddef>
#include <graphics/Pixel.hpp>
#include <string>
#include <vector>

enum class MagicIdentifier { BINARY, ASCII };

class PPM {
public:
  PPM(size_t width = 100, size_t height = 100,
      MagicIdentifier ID = MagicIdentifier::BINARY);

  std::string header() const;

  Pixel &at(size_t row, size_t col);

  void write(size_t row, size_t col, const Pixel &pixel);

  const size_t width;
  const size_t height;
  const std::string magic;
  static const size_t max_color; // only 255 supported

  operator std::string() const {
    std::string retval = header();

    for (size_t row = 0; row < height; ++row)
      for (size_t col = 0; col < width; ++col)
        retval.append(std::string(pixels[row][col]) + '\n');

    return retval;
  }

  std::vector<std::byte> bytes() const {
    std::vector<std::byte> retval;

    for (const char &LETTER : header())
      retval.push_back(static_cast<std::byte>(LETTER));

    for (size_t row = 0; row < height; ++row)
      for (size_t col = 0; col < width; ++col) {
        retval.push_back(pixels[row][col].red);
        retval.push_back(pixels[row][col].green);
        retval.push_back(pixels[row][col].blue);
      }

    return retval;
  }

private:
  void bounds_check(size_t &row, size_t &col) const;

  std::vector<std::vector<Pixel>> pixels;
};

#endif
