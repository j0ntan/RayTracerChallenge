#include <Interactions.hpp>
#include <Math/Transformations.hpp>
#include <Graphics/Canvas.hpp>

struct Scene
{
    Point viewpoint;
    Sphere object;
    double wall_z_coordinate;
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

std::vector<Point> cast_rays(Scene &scene, const Canvas &canvas)
{
    std::vector<Point> points;

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
            if (hit(INTERSECTIONS))
            {
                points.emplace_back(Point(x, y, 0));
            }
        }
    }

    return points;
}
int main()
{
    const std::size_t SIZE = 200;
    Canvas canvas(SIZE, SIZE);

    const double WALL_POSITION = 10;
    Scene scene{Point(0, 0, -5), Sphere(), WALL_POSITION};

    // optional transformations
    // const auto SHRINK_ALONG_Y_AXIS = scaling(1, 0.5, 1);
    // const auto SHRINK_ALONG_X_AXIS = scaling(0.5, 1, 1);
    // const auto SHRINK_AND_ROTATE = rotation_z(PI / 4) * scaling(0.5, 1, 1);
    // const auto SHRINK_AND_SKEW =
    //     shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);
    // SCENE.object.transform = ??;

    const auto POINTS = cast_rays(scene, canvas);
    const Color NICE_RED(0.5, 0, 0);
    for (const auto &POINT : POINTS)
    {
        canvas.write_pixel(POINT.x(), POINT.y(), NICE_RED);
    }

    write_PPM_file(canvas, "shadow");
}
