#include <numbers>
#include <Math/Transformations.hpp>
#include <World/Camera.hpp>
#include <gtest/gtest.h>

/*
Scenario: Constructing a camera
    Given hsize <- 160
        And vsize <- 120
        And field_of_view <- π/2
    When c <- camera(hsize, vsize, field_of_view)
    Then c.hsize = 160
        And c.vsize = 120
        And c.field_of_view = π/2
        And c.transform = identity_matrix
*/
TEST(CameraAttributes, constructCamera)
{
    auto hsize = 160;
    auto vsize = 120;
    auto field_of_view = std::numbers::pi / 2;

    auto c = Camera(hsize, vsize, field_of_view);
    ASSERT_EQ(c.hsize, 160);
    ASSERT_EQ(c.vsize, 120);
    ASSERT_FLOAT_EQ(c.field_of_view, std::numbers::pi / 2);
    ASSERT_EQ(c.transform, IDENTITY);
}

/*
Scenario: The pixel size for a horizontal canvas
    Given c <- camera(200, 125, pi/2)
    Then c.pixel_size = 0.01
*/
TEST(CameraPixelSize, sizeForHorizontalCanvas)
{
    auto c = Camera(200, 125, std::numbers::pi / 2);

    ASSERT_FLOAT_EQ(c.pixel_size, 0.01);
}

/*
Scenario: The pixel size for a vertical canvas
    Given c <- camera(125, 200, pi/2)
    Then c.pixel_size = 0.01
*/
TEST(CameraPixelSize, sizeForVerticalCanvas)
{
    auto c = Camera(125, 200, std::numbers::pi / 2);

    ASSERT_FLOAT_EQ(c.pixel_size, 0.01);
}

/*
Scenario: Constructing a ray through the center of the canvas
    Given c <- camera(201, 101, π/2)
    When r <- ray_for_pixel(c, 100, 50)
    Then r.origin = point(0, 0, 0)
        And r.direction = vector(0, 0, -1)
*/
TEST(ray_for_pixel, rayThroughCenterOfCanvas)
{
    auto c = Camera(201, 101, std::numbers::pi / 2);

    auto r = ray_for_pixel(c, 100, 50);
    ASSERT_EQ(r.origin, Point(0, 0, 0));
    ASSERT_EQ(r.direction, Vector(0, 0, -1));
}

/*
Scenario: Constructing a ray through a corner of the canvas
    Given c <- camera(201, 101, π/2)
    When r <- ray_for_pixel(c, 0, 0)
    Then r.origin = point(0, 0, 0)
        And r.direction = vector(0.66519, 0.33259, -0.66851)
*/
TEST(ray_for_pixel, rayThroughCornerOfCanvas)
{
    auto c = Camera(201, 101, std::numbers::pi / 2);

    auto r = ray_for_pixel(c, 0, 0);
    ASSERT_EQ(r.origin, Point(0, 0, 0));
    ASSERT_EQ(r.direction, Vector(0.66519, 0.33259, -0.66851));
}

/*
Scenario: Constructing a ray when the camera is transformed
    Given c <- camera(201, 101, π/2)
    When c.transform <- rotation_y(π/4) * translation(0, -2, 5)
        And r <- ray_for_pixel(c, 100, 50)
    Then r.origin = point(0, 2, -5)
        And r.direction = vector(√2/2, 0, -√2/2)
*/
TEST(ray_for_pixel, rayWhenCameraTransformed)
{
    auto c = Camera(201, 101, std::numbers::pi / 2);

    c.transform = rotation_y(std::numbers::pi / 4) * translation(0, -2, 5);
    auto r = ray_for_pixel(c, 100, 50);
    ASSERT_EQ(r.origin, Point(0, 2, -5));
    ASSERT_EQ(r.direction,
              Vector(std::numbers::sqrt2 / 2, 0, -std::numbers::sqrt2 / 2));
}

/*
Scenario: Rendering a world with a camera
    Given w <- default_world()
        And c <- camera(11, 11, π/2)
        And from <- point(0, 0, -5)
        And to <- point(0, 0, 0)
        And up <- vector(0, 1, 0)
        And c.transform <- view_transform(from, to, up)
    When image <- render(c, w)
    Then pixel_at(image, 5, 5) = color(0.38066, 0.47583, 0.2855)
*/
TEST(render, renderWorldWithCamera)
{
    auto w = default_world();
    auto c = Camera(11, 11, std::numbers::sqrt2 / 2);
    auto from = Point(0, 0, -5);
    auto to = Point(0, 0, 0);
    auto up = Vector(0, 1, 0);
    c.transform = view_transform(from, to, up);

    auto image = render(c, w);
    ASSERT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}
