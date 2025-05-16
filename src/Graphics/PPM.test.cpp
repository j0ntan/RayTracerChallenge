#include <PPM.hpp>
#include <gtest/gtest.h>

TEST(PPMheader, matchHeader)
{
    std::size_t width = 5, height = 3;
    ASSERT_EQ(std::string("P3\n5 3\n255\n"), PPM::write_header(width, height));
}

TEST(ColorStr, convertEachColor)
{
    Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);

    ASSERT_EQ(PPM::to_string(red), std::string("255 0 0"));
    ASSERT_EQ(PPM::to_string(green), std::string("0 255 0"));
    ASSERT_EQ(PPM::to_string(blue), std::string("0 0 255"));
}

TEST(ColorStr, convertFractionalColor)
{
    Color c(0.25, 0.5, 0.8);

    ASSERT_EQ(PPM::to_string(c), std::string("64 128 204"));
}

TEST(ColorStr, clampToValidRange)
{
    Color c(-1, 2, 0);

    ASSERT_EQ(PPM::to_string(c), std::string("0 255 0"));
}

TEST(SplitLine, keepValidLine)
{
    std::string line = "test\n";
    std::size_t limit = 10;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "test\n");
}

TEST(SplitLine, splitAtLimitReached)
{
    std::string line = "test test\n";
    std::size_t limit = 4;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "test\ntest\n");
}

TEST(SplitLine, splitAtLimitAmount)
{
    std::string line = "a b c d e f\n";
    std::size_t limit = 5;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "a b c\nd e f\n");
}

TEST(SplitLine, splitBeforeTargetWord)
{
    std::string line = "ab cd ef gh ij\n";
    std::size_t limit = 10;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "ab cd ef\ngh ij\n");
}

TEST(SplitLine, splitIntoMultipleLines)
{
    std::string line = "a bb c ddd ee ff gg h iiii jj\n";
    std::size_t limit = 5;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "a bb\nc ddd\nee ff\ngg h\niiii\njj\n");
}

TEST(SplitLine, splitMultiLineString)
{
    std::string line = "a bbb c dd ee\nff gg h iiii jj\n";
    std::size_t limit = 4;

    PPM::split_line(line, limit);
    ASSERT_EQ(line, "a\nbbb\nc dd\nee\nff\ngg h\niiii\njj\n");
}

TEST(WriteData, writeSingleColor)
{
    std::vector<Color> data{Color{0, 0, 0}};

    ASSERT_EQ(PPM::write_data(data, 1), std::string("0 0 0\n"));
}

TEST(WriteData, writeAllColors)
{
    std::vector<Color> data{Color{1, 0, 0}, Color{0, 1, 0}, Color{0, 0, 1}};

    ASSERT_EQ(PPM::write_data(data, 3),
              std::string("255 0 0 0 255 0 0 0 255\n"));
}

TEST(WriteData, splitLineExtending70Chars)
{
    std::vector<Color> data(26, Color(0, 0.1, 0.4));

    std::string expected =
        "0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26\n"
        "102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102\n"
        "0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102 0 26\n"
        "102 0 26 102 0 26 102 0 26 102 0 26 102 0 26 102\n";
    ASSERT_EQ(PPM::write_data(data, 13), expected);
}
