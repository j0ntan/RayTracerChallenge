#include <cmath>
#include <World/Camera.hpp>
#include <Interactions.hpp>

Camera::Camera(std::size_t hsize, std::size_t vsize, double field_of_view)
    : hsize{hsize}, vsize{vsize}, field_of_view{field_of_view}
{
    auto half_view = std::tan(field_of_view / 2);
    auto aspect = static_cast<double>(hsize) / static_cast<double>(vsize);

    if (aspect >= 1)
    {
        half_width = half_view;
        half_height = half_view / aspect;
    }
    else
    {
        half_width = half_view * aspect;
        half_height = half_view;
    }

    pixel_size = (half_width * 2) / hsize;
}

Ray ray_for_pixel(const Camera &camera, std::size_t px, std::size_t py)
{
    // the offset from the edge of the canvas to the pixel's center
    auto xoffset = (px + 0.5) * camera.pixel_size;
    auto yoffset = (py + 0.5) * camera.pixel_size;

    // the untransformed coordinates of the pixel in world space
    // (remember that the camera looks toward -z, so +x is to the *left*)
    auto world_x = camera.half_width - xoffset;
    auto world_y = camera.half_height - yoffset;

    // using the camera matrix, transform the canvas point and the origin
    // and then compute the ray's direction vector
    // (remember that the canvas is at z=-1)
    auto pixel = inverse(camera.transform) * Point(world_x, world_y, -1);
    auto origin = inverse(camera.transform) * Point(0, 0, 0);
    auto direction = normalize(pixel - origin);

    return Ray(origin, direction);
}

Canvas render(const Camera &camera, const World &world)
{
    auto image = Canvas(camera.hsize, camera.vsize);

    for (std::size_t y = 0; y <= camera.vsize - 1; ++y)
    {
        for (std::size_t x = 0; x <= camera.hsize - 1; ++x)
        {
            auto ray = ray_for_pixel(camera, x, y);
            auto color = color_at(world, ray);
            image.write_pixel(x, y, color);
        }
    }

    return image;
}
