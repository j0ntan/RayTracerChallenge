#include <gtest/gtest.h>
#include <primitives/Canvas.hpp>

class Canvas_F : public ::testing::Test {
public:
  const unsigned int WIDTH = 100, HEIGHT = 100;
  Canvas canvas{WIDTH, HEIGHT};
};

TEST_F(Canvas_F, constructBasicCanvas) { Canvas c(WIDTH, HEIGHT); }

TEST_F(Canvas_F, accessWidthAndHeight) {
  unsigned int w = canvas.width;
  unsigned int h = canvas.height;
}

TEST_F(Canvas_F, widthAndHeightAreInitialized) {
  ASSERT_EQ(canvas.width, WIDTH);
  ASSERT_EQ(canvas.height, HEIGHT);
}
