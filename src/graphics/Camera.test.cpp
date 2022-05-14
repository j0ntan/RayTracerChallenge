#include <cmath>
#include <graphics/Camera.hpp>
#include <gtest/gtest.h>
#include <math/Matrix.hpp>
#include <scene/Transformations.hpp>

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

TEST(CameraRay, throughCenterOfCanvas) {
  Camera c(201, 101, HALF_PI);
  Ray r = ray_for_pixel(c, 100, 50);
  ASSERT_EQ(r.origin, (Point{0, 0, 0}));
  ASSERT_EQ(r.direction, (Vector{0, 0, -1}));
}

TEST(CameraRay, throughCornerOfCanvas) {
  Camera c(201, 101, HALF_PI);
  Ray r = ray_for_pixel(c, 0, 0);
  ASSERT_EQ(r.origin, (Point{0, 0, 0}));
  ASSERT_EQ(r.direction, (Vector{0.66519, 0.33259, -0.66851}));
}

TEST(CameraRay, viaTransformedCamera) {
  Camera c(201, 101, HALF_PI);
  c.transform = rotate_y(HALF_PI / 2) * translate(0, -2, 5);
  Ray r = ray_for_pixel(c, 100, 50);
  ASSERT_EQ(r.origin, (Point{0, 2, -5}));
  ASSERT_EQ(r.direction, (Vector{sqrt(2) / 2, 0, -sqrt(2) / 2}));
}
