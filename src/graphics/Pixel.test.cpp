#include <graphics/Pixel.hpp>
#include <gtest/gtest.h>

TEST(Pixel, defaultConstruct) { Pixel pixel; }

TEST(Pixel, constructFromRGBValues) {
  const size_t R = 10;
  const size_t G = 10;
  const size_t B = 10;
  Pixel pixel(R, G, B);
}
