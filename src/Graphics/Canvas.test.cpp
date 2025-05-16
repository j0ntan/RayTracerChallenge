#include <Graphics/Canvas.hpp>
#include <gtest/gtest.h>

/*
Scenario: Creating a canvas
    Given c <- canvas(10, 20)
    Then c.width = 10
        And c.height = 20
*/
TEST(CanvasSize, matchInitializedSize)
{
    auto c = Canvas(10, 20);

    ASSERT_EQ(c.WIDTH, 10);
    ASSERT_EQ(c.HEIGHT, 20);
}

/*
Scenario: Writing pixels to a canvas
    Given c <- canvas(10, 20)
        And red <- color(1, 0, 0)
    When write_pixel(c, 2, 3, red)
    Then pixel_at(c, 2, 3) = red
*/
TEST(CanvasWrite, matchWrittenPixel)
{
    auto c = Canvas{10, 20};
    auto red = Color{1, 0, 0};
    c.write_pixel(2, 3, red);
    ASSERT_EQ((c.pixel_at(2, 3)), (red));
}

TEST(CanvasPPM, writeOutputString)
{
    Canvas c{10, 20};
    std::string output = c.write_ppm();
}

/*
Scenario: Constructing the PPM header
    Given c <- canvas(5, 3)
    When ppm <- canvas_to_ppm(c)
    Then lines 1-3 of ppm are
        """
        P3
        5 3
        255
        """
*/
TEST(CanvasPPM, useCorrectHeaderFormat)
{
    auto c = Canvas{5, 3};
    auto ppm = c.write_ppm();

    ASSERT_TRUE(ppm.starts_with("P3\n5 3\n255\n"));
}

/*
Scenario: Constructing the PPM pixel data
    Given c <- canvas(5, 3)
        And c1 <- color(1.5, 0, 0)
        And c2 <- color(0, 0.5, 0)
        And c3 <- color(-0.5, 0, 1)
    When write_pixel(c, 0, 0, c1)
        And write_pixel(c, 2, 1, c2)
        And write_pixel(c, 4, 2, c3)
        And ppm <- canvas_to_ppm(c)
    Then lines 4-6 of ppm are
    """
    255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
    """
*/
TEST(CanvasPPM, writePPMpixels)
{
    auto c = Canvas{5, 3};
    auto c1 = Color{1.5, 0, 0};
    auto c2 = Color{0, 0.5, 0};
    auto c3 = Color{-0.5, 0, 1};

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    auto ppm = c.write_ppm();
    ASSERT_TRUE(ppm.ends_with(
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"));
}

TEST(CanvasPPM, fillWithSelectedColor)
{
    Canvas canvas(5, 3);
    Color color(1.23, 4.56, 7.89);

    canvas.fill_pixels(color);

    ASSERT_EQ(canvas.pixel_at(0, 0), color);
    ASSERT_EQ(canvas.pixel_at(0, 1), color);
    ASSERT_EQ(canvas.pixel_at(0, 2), color);
    ASSERT_EQ(canvas.pixel_at(1, 0), color);
    ASSERT_EQ(canvas.pixel_at(1, 1), color);
    ASSERT_EQ(canvas.pixel_at(1, 2), color);
    ASSERT_EQ(canvas.pixel_at(2, 0), color);
    ASSERT_EQ(canvas.pixel_at(2, 1), color);
    ASSERT_EQ(canvas.pixel_at(2, 2), color);
    ASSERT_EQ(canvas.pixel_at(3, 0), color);
    ASSERT_EQ(canvas.pixel_at(3, 1), color);
    ASSERT_EQ(canvas.pixel_at(3, 2), color);
    ASSERT_EQ(canvas.pixel_at(4, 0), color);
    ASSERT_EQ(canvas.pixel_at(4, 1), color);
    ASSERT_EQ(canvas.pixel_at(4, 2), color);
}

/*
Scenario: Splitting long lines in PPM files
    Given c <- canvas(10, 2)
    When every pixel of c is set to color(1, 0.8, 0.6)
        And ppm <- canvas_to_ppm(c)
    Then lines 4-7 of ppm are
        """
        255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
        153 255 204 153 255 204 153 255 204 153 255 204 153
        255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
        153 255 204 153 255 204 153 255 204 153 255 204 153
        """
*/
TEST(CanvasPPM, splitLongLines)
{
    auto c = Canvas(10, 2);
    c.fill_pixels(Color(1, 0.8, 0.6));
    auto ppm = c.write_ppm();

    ASSERT_TRUE(ppm.ends_with(
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"));
}

/*
Scenario: PPM files are terminated by a newline character
    Given c <- canvas(5, 3)
    When ppm <- canvas_to_ppm(c)
    Then ppm ends with a newline character
*/
TEST(CanvasPPM, endsWithNewline)
{
    auto c = Canvas(5, 3);
    auto ppm = c.write_ppm();

    ASSERT_EQ(ppm.back(), '\n');
}
