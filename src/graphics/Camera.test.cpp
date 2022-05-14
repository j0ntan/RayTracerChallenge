#include <cmath>
#include <graphics/Camera.hpp>
#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(Camera, constructCamera) {
  std::size_t hsize = 160;
  std::size_t vsize = 120;
  auto field_of_view = asin(1); // pi / 2
  Camera c{hsize, vsize, field_of_view};
  ASSERT_EQ(c.hsize, hsize);
  ASSERT_EQ(c.vsize, vsize);
  ASSERT_EQ(c.field_of_view, field_of_view);
  ASSERT_EQ(c.transform, identity);
}
