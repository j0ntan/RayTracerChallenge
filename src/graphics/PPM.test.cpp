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
