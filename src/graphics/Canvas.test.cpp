#include <graphics/Canvas.hpp>
#include <gtest/gtest.h>
#include <sstream>

class Canvas_F : public ::testing::Test {
public:
  const unsigned int WIDTH = 100, HEIGHT = 100;
  Canvas canvas{WIDTH, HEIGHT};
};

class Canvas_PPM_F : public ::testing::Test {
public:
  const unsigned int WIDTH = 5, HEIGHT = 3;
  Canvas canvas{WIDTH, HEIGHT};
  std::stringstream str_stream;
  const std::string HEADER = "P3\n5 3\n255\n";
};

TEST_F(Canvas_F, constructBasicCanvas) { Canvas c(WIDTH, HEIGHT); }

TEST_F(Canvas_F, widthAndHeightAreInitialized) {
  ASSERT_EQ(canvas.width, WIDTH);
  ASSERT_EQ(canvas.height, HEIGHT);
}

TEST_F(Canvas_F, getColorFromPixel) { Color c = canvas.pixel(0, 0); }

TEST_F(Canvas_F, allPixelsDefaultToBlack) {
  const Color black{0, 0, 0};
  for (unsigned x = 0; x < WIDTH; ++x)
    for (unsigned y = 0; y < HEIGHT; ++y)
      ASSERT_EQ(canvas.pixel(x, y), black);
}

TEST_F(Canvas_F, writeColorToPixelAtXYCoordinates) {
  const Color red(1, 0, 0), blue(0, 1, 0);
  canvas.write(2, 3, red);
  canvas.write(4, 8, blue);
  ASSERT_EQ(canvas.pixel(2, 3), red);
  ASSERT_EQ(canvas.pixel(4, 8), blue);
}

TEST_F(Canvas_PPM_F, writePPMHeader) {
  canvas.to_ppm(str_stream);
  auto output_header = str_stream.str().substr(0, HEADER.length());
  ASSERT_EQ(output_header, HEADER);
}

TEST_F(Canvas_PPM_F, writePPMDefaultPixelsData) {
  const std::string DEFAULT_PIXELS_DATA = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
  canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(HEADER.length());
  ASSERT_EQ(output_pixels_data, DEFAULT_PIXELS_DATA);
}

TEST_F(Canvas_PPM_F, writeSingleWhitePixelData) {
  const std::string SINGLE_WHITE_PIXEL_DATA =
      "255 255 255 0 0 0 0 0 0 0 0 0 0 0 0\n"
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
  canvas.write(0, 0, Color(1, 1, 1));
  canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(HEADER.length());
  ASSERT_EQ(output_pixels_data, SINGLE_WHITE_PIXEL_DATA);
}

TEST_F(Canvas_PPM_F, writeFractionalColorsPixelData) {
  const Color c(.2, .4, .8); // these values scale up to an integer
  const std::string FRACTIONAL_COLOR_PIXEL_DATA =
      "51 102 204 0 0 0 0 0 0 0 0 0 0 0 0\n"
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
  canvas.write(0, 0, c);
  canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(HEADER.length());
  ASSERT_EQ(output_pixels_data, FRACTIONAL_COLOR_PIXEL_DATA);
}

TEST_F(Canvas_PPM_F, roundFractionalColorsAfterScaling) {
  const Color c(.123, .5, .789);
  const std::string ROUNDED_PIXEL_DATA = "31 128 201 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                         "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                         "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
  canvas.write(0, 0, c);
  canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(HEADER.length());
  ASSERT_EQ(output_pixels_data, ROUNDED_PIXEL_DATA);
}

TEST_F(Canvas_PPM_F, pixelDataIsBounded) {
  const Color c(1.1, 0, 100);
  const std::string BOUNDED_PIXEL_DATA = "255 0 255 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                         "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                         "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
  canvas.write(0, 0, c);
  canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(HEADER.length());
  ASSERT_EQ(output_pixels_data, BOUNDED_PIXEL_DATA);
}

TEST_F(Canvas_PPM_F, pixelDataLengthIs70CharactersOrLess) {
  Canvas large_canvas(10, 2);
  const std::string THIS_HEADER = "P3\n10 2\n255\n";
  const std::string WRAP_AROUND_PIXEL_DATA =
      "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255\n"
      "255 255 255 255 255 255 255 255 255 255 255 255 255\n"
      "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255\n"
      "255 255 255 255 255 255 255 255 255 255 255 255 255\n";

  // fill with white color, which is written as 3 digits after scaling
  for (size_t x = 0; x < 10; ++x)
    for (size_t y = 0; y < 2; ++y)
      large_canvas.write(x, y, Color(1, 1, 1));

  large_canvas.to_ppm(str_stream);
  auto output_pixels_data = str_stream.str().substr(THIS_HEADER.length());
  ASSERT_EQ(output_pixels_data, WRAP_AROUND_PIXEL_DATA);
}

TEST_F(Canvas_PPM_F, writeOutputFile) { canvas.to_ppm_file("sample_ppm"); }
