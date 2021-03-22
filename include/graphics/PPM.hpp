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

private:
  void bounds_check(size_t &row, size_t &col) const;

  std::vector<std::vector<Pixel>> pixels;
};

#endif
