#include <numbers>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Math/Plane.hpp>
#include <World/Camera.hpp>
#include <Graphics/CheckerPattern.hpp>
#include <Graphics/StripePattern.hpp>

/**
 * @brief Canvas parameters for rendering the scene
 *
 */
constexpr double CANVAS_SCALE = 10;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE,
                      VSIZE = 50 * CANVAS_SCALE;

/**
 * @brief Create & place the world's objects for rendering
 *
 * @return World The specified world
 */
World create_world()
{
    World world;
    const auto ROOM_REFLECTIVENESS = 0.2;

    // 1. The floor is a plane with a white/gray checker pattern
    Plane floor;
    floor.material.ambient = 0.0;
    floor.material.reflective = ROOM_REFLECTIVENESS;
    floor.material.pattern =
        std::make_unique<CheckerPattern>(Color::WHITE, Color(0.35, 0.35, 0.35));
    const auto CHECKER_PATTERN_SCALE = 0.5;
    floor.material.pattern->transform =
        rotation_y((10.0 / 180.0) * std::numbers::pi) *
        scaling(CHECKER_PATTERN_SCALE, CHECKER_PATTERN_SCALE,
                CHECKER_PATTERN_SCALE);

    // 2. Arrange walls (assume origin at intersection)

    // left wall
    Plane left_wall;
    left_wall.material.color = Color(1, 0, 0);
    left_wall.material.ambient = 0.8;
    left_wall.material.diffuse = 0;
    left_wall.material.specular = 0;
    left_wall.material.reflective = ROOM_REFLECTIVENESS;
    left_wall.transform = rotation_y(std::numbers::pi / 2) *
                          rotation_x(std::numbers::pi / 2);
    left_wall.material.pattern = std::make_unique<StripePattern>(
        Color(0.22, 0.22, 0.22), Color(0.3, 0.3, 0.3));
    const auto WALL_STRIPE_SCALE = 0.55;
    left_wall.material.pattern->transform =
        scaling(1, 1, WALL_STRIPE_SCALE) *
        rotation_y(std::numbers::pi / 2);

    // front wall
    Plane front_wall = left_wall;
    front_wall.transform = rotation_x(std::numbers::pi / 2);
    front_wall.material.pattern->transform =
        translation(0, 0, WALL_STRIPE_SCALE) *
        front_wall.material.pattern->transform;

    // 3. Arrange marbles
    const auto SMALL_MRBL_SCALE = 0.5;
    const auto SMALLER_MRBL_SCALE = 0.25;

    // left wall marbles
    Sphere green_marble;
    const Point GR_MRBL_CENTER(SMALL_MRBL_SCALE,
                               SMALL_MRBL_SCALE,
                               SMALL_MRBL_SCALE + 6.5);
    const auto GR_MRBL_OFFSET = SMALL_MRBL_SCALE + 6.5;
    green_marble.transform =
        translation(SMALL_MRBL_SCALE, SMALL_MRBL_SCALE, -GR_MRBL_OFFSET) *
        scaling(SMALL_MRBL_SCALE, SMALL_MRBL_SCALE, SMALL_MRBL_SCALE);
    green_marble.material.color = Color(0.5961, 1, 0.5961);
    green_marble.material.ambient = 0.4;
    green_marble.material.diffuse = 0.7;
    green_marble.material.specular = 0.8;
    green_marble.material.shininess = 30;

    Sphere blue_marble;
    const auto BL_MRBL_OFFSET = GR_MRBL_OFFSET + SMALL_MRBL_SCALE +
                                SMALLER_MRBL_SCALE;
    blue_marble.transform =
        translation(SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE, -BL_MRBL_OFFSET) *
        scaling(SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE);
    blue_marble.material.color = Color(0.5294, 0.8078, 0.9216);
    blue_marble.material.ambient = 0.4;
    blue_marble.material.diffuse = 0.7;
    blue_marble.material.specular = 0.8;
    blue_marble.material.shininess = 60;

    // center marbles
    Sphere red_marble;
    red_marble.transform =
        translation(GR_MRBL_OFFSET / 2 - 1, 0.5, -GR_MRBL_OFFSET / 2 - 1);
    red_marble.material.color = Color(0.7529, 0.2745, 0.3412);
    red_marble.material.ambient = 0.4;
    red_marble.material.diffuse = 0.7;
    red_marble.material.specular = 0.4;
    red_marble.material.shininess = 5;

    // clear green marble
    Sphere clear_green_marble = glass_sphere();
    clear_green_marble.transform =
        translation(GR_MRBL_OFFSET / 2 + 0.2, 0.25,
                    -GR_MRBL_OFFSET / 2 - 0.92) *
        scaling(SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE);
    clear_green_marble.material.color = Color(0.1804, 0.4353, 0.2510);
    clear_green_marble.material.ambient = 0.4;
    clear_green_marble.material.diffuse = 0.3;
    clear_green_marble.material.specular = 0.8;
    clear_green_marble.material.shininess = 200;
    clear_green_marble.material.transparency = 0.4;

    // clear blue marble
    Sphere clear_blue_marble = glass_sphere();
    clear_blue_marble.transform =
        translation(3.7, 0.5, -3.62) *
        scaling(SMALL_MRBL_SCALE, SMALL_MRBL_SCALE, SMALL_MRBL_SCALE);
    clear_blue_marble.material.color = Color(0.1882, 0.1529, 0.4863);
    clear_blue_marble.material.ambient = 0.4;
    clear_blue_marble.material.diffuse = 0.3;
    clear_blue_marble.material.specular = 0.8;
    clear_blue_marble.material.shininess = 200;
    clear_blue_marble.material.transparency = 0.6;

    // front wall marbles
    Sphere orange_marble;
    const auto ORNG_MRBL_OFFSET = SMALL_MRBL_SCALE + 3.5;
    orange_marble.transform =
        translation(ORNG_MRBL_OFFSET, SMALL_MRBL_SCALE, -SMALL_MRBL_SCALE) *
        scaling(SMALL_MRBL_SCALE, SMALL_MRBL_SCALE, SMALL_MRBL_SCALE);
    orange_marble.material.color = Color(0.7004, 0.4402, 0.3422);
    orange_marble.material.ambient = 0.4;
    orange_marble.material.diffuse = 0.7;
    orange_marble.material.specular = 0.8;
    orange_marble.material.shininess = 30;

    Sphere pink_marble;
    const auto PINK_MRBL_OFFSET = ORNG_MRBL_OFFSET + SMALL_MRBL_SCALE +
                                  SMALLER_MRBL_SCALE;
    pink_marble.transform =
        translation(PINK_MRBL_OFFSET, SMALLER_MRBL_SCALE, -SMALLER_MRBL_SCALE) *
        scaling(SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE, SMALLER_MRBL_SCALE);
    pink_marble.material.color = Color(1.0, 0.4588, 0.8471);
    pink_marble.material.ambient = 0.4;
    pink_marble.material.diffuse = 0.7;
    pink_marble.material.specular = 0.8;
    pink_marble.material.shininess = 60;

    // add shapes to return value
    world.objects.push_back(std::make_shared<Plane>(floor));
    world.objects.push_back(std::make_shared<Plane>(left_wall));
    world.objects.push_back(std::make_shared<Plane>(front_wall));
    world.objects.push_back(std::make_shared<Sphere>(blue_marble));
    world.objects.push_back(std::make_shared<Sphere>(green_marble));
    world.objects.push_back(std::make_shared<Sphere>(red_marble));
    world.objects.push_back(std::make_shared<Sphere>(clear_green_marble));
    world.objects.push_back(std::make_shared<Sphere>(clear_blue_marble));
    world.objects.push_back(std::make_shared<Sphere>(orange_marble));
    world.objects.push_back(std::make_shared<Sphere>(pink_marble));

    // The light source is white, shining from back of the room
    world.light = std::make_shared<PointLight>(Point(1.8, 8, -10),
                                               Color(1, 1, 1));

    return world;
}

int main()
{
    auto world = create_world();
    Camera camera(HSIZE, VSIZE, 140 * std::numbers::pi / 180);

    // position the camera to face the corner, slightly offset to the left
    camera.transform = view_transform(Point(4.35, 0.8, -4.5), Point(0, 0, -2.1),
                                      Vector(0, 1, 0));

    auto canvas = render(camera, world);
    write_PPM_file(canvas, "marbles");
}
