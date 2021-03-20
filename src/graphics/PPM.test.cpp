#include <graphics/PPM.hpp>
#include <gtest/gtest.h>

TEST(PPM, createMagicIdentifiers) {
  auto bin = MagicIdentifier::BINARY;
  auto txt = MagicIdentifier::ASCII;
}

TEST(PPM, constructWithSpecifiedSizeAndIdentifier) {
  PPM ppm(100, 100, MagicIdentifier::ASCII);
}

TEST(PPM, constructWithDefaultSizeAndIdentifier) { PPM ppm; }

TEST(PPM, getMagicIdentifier) {
  PPM ppm;
  const std::string ID = ppm.magic;
}

TEST(PPM, matchGivenIdentifier) {
  PPM ppm1(1, 1, MagicIdentifier::ASCII), ppm2(1, 1, MagicIdentifier::BINARY);
  ASSERT_EQ(ppm1.magic, "P3");
  ASSERT_EQ(ppm2.magic, "P6");
}

TEST(PPM, matchDefaultIdentifer) {
  PPM ppm;
  ASSERT_EQ(ppm.magic, "P6");
}

TEST(PPM, getWidthAndHeight) {
  PPM ppm;
  size_t width = ppm.width;
  size_t height = ppm.height;
}

TEST(PPM, matchDefaultWidthAndHeight) {
  PPM ppm;
  ASSERT_EQ(ppm.width, 100);
  ASSERT_EQ(ppm.height, 100);
}

TEST(PPM, matchGivenWidthAndHeight) {
  PPM ppm(123, 456);
  ASSERT_EQ(ppm.width, 123);
  ASSERT_EQ(ppm.height, 456);
}

TEST(PPM, getMaxColor) {
  PPM ppm;
  size_t max_color = ppm.max_color;
  size_t static_max_color = PPM::max_color;
}

TEST(PPM, maxColorIs255) { ASSERT_EQ(PPM::max_color, 255); }

TEST(PPM, getHeader) {
  const PPM ppm;
  std::string header = ppm.header();
}

TEST(PPM, matchHeaderForDefaultValues) {
  const PPM ppm;
  ASSERT_EQ(ppm.header(), "P6\n"
                          "100 100\n"
                          "255\n");
}

TEST(PPM, matchHeaderWithGivenValues) {
  const PPM ppm(123, 456, MagicIdentifier::ASCII);
  ASSERT_EQ(ppm.header(), "P3\n"
                          "123 456\n"
                          "255\n");
}
