#include <utility>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Interactions.hpp>
#include <Lighting.hpp>
#include <Graphics/Canvas.hpp>

struct Scene
{
    Point viewpoint;
    Sphere object;
    double wall_z_coordinate;
    PointLight source;
};

double calculate_wall_size(const Scene &scene)
{
    // reference data
    const Point GLOBAL_ORIGIN(0, 0, 0);
    const double GLOBAL_RADIUS = 1;
    const Point WALL_POINT(0, 0, scene.wall_z_coordinate);

    // calculate distances & diameter
    const double DISTANCE_TO_SPHERE = magnitude(GLOBAL_ORIGIN -
                                                scene.viewpoint);
    const double DISTANCE_TO_WALL = magnitude(WALL_POINT - scene.viewpoint);
    const double SHADOW_DIAMETER =
        (GLOBAL_RADIUS / DISTANCE_TO_SPHERE * DISTANCE_TO_WALL) * 2;

    return 1.25 * SHADOW_DIAMETER; // make wall slightly larger than shadow
}

std::vector<std::pair<Point, Color>>
cast_rays(Scene &scene, const Canvas &canvas)
{
    std::vector<std::pair<Point, Color>> pixels;

    const double WALL_SIZE = calculate_wall_size(scene);
    const double PIXEL_SIZE = WALL_SIZE / canvas.HEIGHT;

    for (std::size_t y = 0; y < canvas.HEIGHT; ++y)
    {
        const double WORLD_Y = (WALL_SIZE / 2) - PIXEL_SIZE * y;
        for (std::size_t x = 0; x < canvas.WIDTH; ++x)
        {
            const double WORLD_X = -(WALL_SIZE / 2) + PIXEL_SIZE * x;

            const Point POINT_ON_WALL(WORLD_X, WORLD_Y,
                                      scene.wall_z_coordinate);
            const Ray RAY{.origin = scene.viewpoint,
                          .direction = Vector(
                              normalize(POINT_ON_WALL - scene.viewpoint))};

            const auto INTERSECTIONS = intersect(scene.object, RAY);
            if (const auto HIT = hit(INTERSECTIONS))
            {
                auto point = position(RAY, HIT->t);
                auto normal = HIT->object->normal_at(point);
                auto eye = -RAY.direction;
                auto color = lighting(HIT->object->material, scene.source,
                                      scene.viewpoint, eye, normal);
                pixels.emplace_back(std::make_pair(Point(x, y, 0), color));
            }
        }
    }

    return pixels;
}

int main()
{
    const std::size_t SIZE = 800;
    Canvas canvas(SIZE, SIZE);

    const Point VIEWPOINT{0, 0, -5};
    const double WALL_POSITION = 10;
    const Point LIGHT_POSITION{-10, 10, -10};
    const Color LIGHT_INTENSITY{1, 1, 1};
    const Color SPHERE_COLOR{1, 0.2, 1};
    Scene scene{
        .viewpoint = VIEWPOINT,
        .object = Sphere(),
        .wall_z_coordinate = WALL_POSITION,
        .source = PointLight{.position = LIGHT_POSITION,
                             .intensity = LIGHT_INTENSITY}};
    scene.object.material.color = SPHERE_COLOR;

    // optional transformations
    // const auto SHRINK_ALONG_Y_AXIS = scaling(1, 0.5, 1);
    // const auto SHRINK_ALONG_X_AXIS = scaling(0.5, 1, 1);
    // const auto SHRINK_AND_ROTATE = rotation_z(PI / 4) * scaling(0.5, 1, 1);
    // const auto SHRINK_AND_SKEW =
    //     shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);
    // SCENE.object.transform = ??;

    const auto PIXELS = cast_rays(scene, canvas);
    for (const auto &PIXEL : PIXELS)
    {
        canvas.write_pixel(PIXEL.first.x(), PIXEL.first.y(),
                           PIXEL.second);
    }

    write_PPM_file(canvas, "3D_sphere");
}
