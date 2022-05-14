#include <gtest/gtest.h>
#include <scene/Transformations.hpp>
#include <scene/View.hpp>

TEST(ViewTransform, defaultOrientation) {
  auto from = Point(0, 0, 0);
  auto to = Point(0, 0, -1);
  auto up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  ASSERT_EQ(t, identity);
}

TEST(ViewTransform, inPositiveZDirection) {
  auto from = Point(0, 0, 0);
  auto to = Point(0, 0, 1);
  auto up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  ASSERT_EQ(t, scale(-1, 1, -1));
}

TEST(ViewTransform, worldIsMoved) {
  auto from = Point(0, 0, 8);
  auto to = Point(0, 0, 0);
  auto up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  ASSERT_EQ(t, translate(0, 0, -8));
}

TEST(ViewTransform, arbitraryView) {
  auto from = Point(1, 3, 2);
  auto to = Point(4, -2, 8);
  auto up = Vector(1, 1, 0);
  auto t = view_transform(from, to, up);
  Matrix<4> m = {{-0.50709, 0.50709, 0.67612, -2.36643},
                 {0.76772, 0.60609, 0.12122, -2.82843},
                 {-0.35857, 0.59761, -0.71714, 0.00000},
                 {0.00000, 0.00000, 0.00000, 1.00000}};
  ASSERT_EQ(t, m);
}
