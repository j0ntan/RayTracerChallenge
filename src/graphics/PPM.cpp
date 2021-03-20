#include <graphics/PPM.hpp>

const size_t PPM::max_color = 255;

PPM::PPM(size_t width, size_t height, MagicIdentifier ID)
    : width{width}, height{height}, magic{ID == MagicIdentifier::ASCII ? "P3"
                                                                       : "P6"},
      pixels{std::vector<std::vector<Pixel>>(
          height, std::vector<Pixel>(width, Pixel()))} {}

std::string PPM::header() const {
  return magic + '\n' + std::to_string(width) + ' ' + std::to_string(height) +
         '\n' + "255\n";
}

Pixel &PPM::at(size_t row, size_t col) { return pixels[row][col]; }
