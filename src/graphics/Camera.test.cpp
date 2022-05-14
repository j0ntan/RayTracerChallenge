#include <cmath>
#include <graphics/Camera.hpp>
#include <gtest/gtest.h>
#include <math/Matrix.hpp>

const auto HALF_PI = asin(1);

TEST(Camera, constructCamera) {
  std::size_t hsize = 160;
  std::size_t vsize = 120;
  auto field_of_view = HALF_PI;
  Camera c{hsize, vsize, field_of_view};
  ASSERT_EQ(c.hsize, hsize);
  ASSERT_EQ(c.vsize, vsize);
  ASSERT_EQ(c.field_of_view, field_of_view);
  ASSERT_EQ(c.transform, identity);
}

TEST(Camera, pixelSizeForHorizontalCanvas) {
  Camera c{200, 125, HALF_PI};
  ASSERT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(Camera, pixelSizeForVerticalCanvas) {
  Camera c{125, 200, HALF_PI};
  ASSERT_FLOAT_EQ(c.pixel_size, 0.01);
}
