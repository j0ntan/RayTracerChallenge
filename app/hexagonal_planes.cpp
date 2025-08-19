#include <numbers>
#include <fstream>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Math/Plane.hpp>
#include <World/Camera.hpp>

/**
 * @brief Canvas parameters for rendering the scene
 *
 */
constexpr double CANVAS_SCALE = 14;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE,
                      VSIZE = 50 * CANVAS_SCALE;

/**
 * @brief Length of each hexagon wall
 *
 */
constexpr double WALL_L = 5;

/**
 * @brief Constant provided for convenience
 *
 */
constexpr double HALF_ROOT_3 = std::numbers::sqrt3 / 2;

/**
 * @brief Create the world according to the book's description.
 *
 * @return World The specified world
 */
World create_world()
{
    World world;

    // 1. The floor/ceiling is a plane with a matte texture.
    Plane floor;
    floor.material = Material();
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Plane ceiling(floor);
    ceiling.transform = translation(0, WALL_L, 0);

    // 2. Arrange walls in a regular hexagon shape
    Plane front_wall(floor);
    front_wall.transform = translation(0, 0, WALL_L * HALF_ROOT_3) *
                           rotation_x(std::numbers::pi / 2);
    front_wall.material.color = Color(0.8627, 0.0784, 0.2353); // red

    Plane front_left_wall(floor);
    front_left_wall.transform = translation(-WALL_L, 0, 0) *
                                rotation_y(-std::numbers::pi / 3) *
                                rotation_x(std::numbers::pi / 2);
    front_left_wall.material.color = Color(0.1333, 0.5451, 0.1333); // green

    Plane front_right_wall(floor);
    front_right_wall.transform = translation(WALL_L, 0, 0) *
                                 rotation_y(std::numbers::pi / 3) *
                                 rotation_x(std::numbers::pi / 2);
    front_right_wall.material.color = Color(0.1176, 0.5647, 1.0); // blue

    Plane back_wall(floor);
    back_wall.transform = translation(0, 0, -WALL_L * HALF_ROOT_3) *
                          rotation_x(std::numbers::pi / 2);
    back_wall.material.color = Color(1.0, 0.5490, 0.0); // orange

    Plane back_left_wall(floor);
    back_left_wall.transform = translation(-WALL_L, 0, 0) *
                               rotation_y(std::numbers::pi / 3) *
                               rotation_x(std::numbers::pi / 2);
    back_left_wall.material.color = Color(0.5412, 0.1686, 0.8863); // purple

    Plane back_right_wall(floor);
    back_right_wall.transform = translation(WALL_L, 0, 0) *
                                rotation_y(-std::numbers::pi / 3) *
                                rotation_x(std::numbers::pi / 2);
    back_right_wall.material.color = Color(0.0, 0.5020, 0.5020); // teal

    // 3. The large sphere in the middle is a unit sphere, translated upward
    // slightly and colored green.
    Sphere middle_sphere;
    middle_sphere.transform = translation(-0.5, 1, 0.5);
    middle_sphere.material = Material();
    middle_sphere.material.color = Color(0.1, 1, 0.5);
    middle_sphere.material.diffuse = 0.7;
    middle_sphere.material.specular = 0.3;

    // 4. The smaller green sphere on the right is scaled in half.
    Sphere right_sphere;
    right_sphere.transform = translation(1.5, 0.5, -0.5) *
                             scaling(0.5, 0.5, 0.5);
    right_sphere.material = Material();
    right_sphere.material.color = Color(0.5, 1, 0.1);
    right_sphere.material.diffuse = 0.7;
    right_sphere.material.specular = 0.3;

    // 5. The smallest is scaled by a third, before being translated.
    Sphere left_sphere;
    left_sphere.transform = translation(-1.5, 0.33, -0.75) *
                            scaling(0.33, 0.33, 0.33);
    left_sphere.material = Material();
    left_sphere.material.color = Color{1, 0.8, 0.1};
    left_sphere.material.diffuse = 0.7;
    left_sphere.material.specular = 0.3;

    // add shapes to return value
    world.objects.push_back(std::make_shared<Plane>(floor));
    world.objects.push_back(std::make_shared<Plane>(ceiling));
    world.objects.push_back(std::make_shared<Plane>(front_wall));
    world.objects.push_back(std::make_shared<Plane>(front_left_wall));
    world.objects.push_back(std::make_shared<Plane>(front_right_wall));
    world.objects.push_back(std::make_shared<Plane>(back_wall));
    world.objects.push_back(std::make_shared<Plane>(back_left_wall));
    world.objects.push_back(std::make_shared<Plane>(back_right_wall));
    world.objects.push_back(std::make_shared<Sphere>(left_sphere));
    world.objects.push_back(std::make_shared<Sphere>(middle_sphere));
    world.objects.push_back(std::make_shared<Sphere>(right_sphere));

    // The light source is white, shining from above and to the left:
    world.light = std::make_shared<PointLight>(Point(-1.4, 2, -2),
                                               Color(1, 1, 1));

    return world;
}

int main()
{
    auto world = create_world();
    Camera camera(HSIZE, VSIZE, 140 * std::numbers::pi / 180);

    // offset used to position the camera slightly away from corner
    const double DEL = 0.3;

    // place camera in corner in the 4th quadrant in xz-plane, facing center
    camera.transform = view_transform(
        Point(WALL_L / 2 - DEL, 1.5, -WALL_L * HALF_ROOT_3 + DEL),
        Point(0, 2.4, 0),
        Vector(0, 1, 0));

    auto canvas = render(camera, world);
    write_PPM_file(canvas, "hexagonal_planes");
}
