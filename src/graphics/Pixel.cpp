#include <graphics/Pixel.hpp>

Pixel::Pixel() : red{}, green{}, blue{} {}

Pixel::Pixel(size_t R, size_t G, size_t B)
    : red{R <= 255 ? static_cast<std::byte>(R) : std::byte{255}},
      green{G <= 255 ? static_cast<std::byte>(G) : std::byte{255}},
      blue{B <= 255 ? static_cast<std::byte>(B) : std::byte{255}} {}
