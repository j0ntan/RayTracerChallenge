#include <graphics/Pixel.hpp>
#include <gtest/gtest.h>

TEST(Pixel, defaultConstruct) { Pixel pixel; }

TEST(Pixel, constructFromRGBValues) {
  const size_t R = 10;
  const size_t G = 10;
  const size_t B = 10;
  Pixel pixel(R, G, B);
}

TEST(Pixel, readPixelValues) {
  const Pixel pixel;
  const std::byte red = pixel.red;
  const std::byte green = pixel.green;
  const std::byte blue = pixel.blue;
}

TEST(Pixel, defaultPixelValuesAreZero) {
  const Pixel pixel;
  ASSERT_EQ(pixel.red, std::byte{0});
  ASSERT_EQ(pixel.green, std::byte{0});
  ASSERT_EQ(pixel.blue, std::byte{0});
}

TEST(Pixel, readGivenPixelValues) {
  const Pixel pixel(1, 2, 3);
  ASSERT_EQ(pixel.red, std::byte{1});
  ASSERT_EQ(pixel.green, std::byte{2});
  ASSERT_EQ(pixel.blue, std::byte{3});
}

TEST(Pixel, clampValuesTo255) {
  const Pixel AT_MAX(255, 255, 255);
  ASSERT_EQ(AT_MAX.red, std::byte{255});
  ASSERT_EQ(AT_MAX.green, std::byte{255});
  ASSERT_EQ(AT_MAX.blue, std::byte{255});

  const Pixel CLAMPED(300, 400, 500);
  ASSERT_EQ(CLAMPED.red, std::byte{255});
  ASSERT_EQ(CLAMPED.green, std::byte{255});
  ASSERT_EQ(CLAMPED.blue, std::byte{255});
}
