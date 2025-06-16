#include <numbers>
#include <fstream>
#include <Math/Transformations.hpp>
#include <World/Camera.hpp>

/**
 * @brief Canvas parameters for rendering the scene
 *
 */
constexpr double CANVAS_SCALE = 10;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE,
                      VSIZE = 50 * CANVAS_SCALE;

/**
 * @brief Create the world according to the book's description.
 *
 * @return World The specified world
 */
World create_world()
{
    World world;

    // 1. The floor is an extremely flattened sphere with a matte texture.
    Sphere floor;
    floor.transform = scaling(10, 0.01, 10);
    floor.material = Material();
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    // 2. The wall on the left has the same scale and color as the floor, but
    // is also rotated and translated into place.
    Sphere left_wall;
    left_wall.transform = translation(0, 0, 5) *
                          rotation_y(-std::numbers::pi / 4) *
                          rotation_x(std::numbers::pi / 2) *
                          scaling(10, 0.01, 10);
    left_wall.material = floor.material;

    // 3. The wall on the right is identical to the left wall, but is rotated
    // the opposite direction in y.
    Sphere right_wall;
    right_wall.transform = translation(0, 0, 5) *
                           rotation_y(std::numbers::pi / 4) *
                           rotation_x(std::numbers::pi / 2) *
                           scaling(10, 0.01, 10);
    right_wall.material = floor.material;

    // 4. The large sphere in the middle is a unit sphere, translated upward
    // slightly and colored green.
    Sphere middle;
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = Material();
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    // 5. The smaller green sphere on the right is scaled in half.
    Sphere right;
    right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right.material = Material();
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    // 6. The smallest is scaled by a third, before being translated.
    Sphere left;
    left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left.material = Material();
    left.material.color = Color{1, 0.8, 0.1};
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    // add spheres to return value
    world.objects.push_back(std::make_shared<Sphere>(floor));
    world.objects.push_back(std::make_shared<Sphere>(left_wall));
    world.objects.push_back(std::make_shared<Sphere>(right_wall));
    world.objects.push_back(std::make_shared<Sphere>(left));
    world.objects.push_back(std::make_shared<Sphere>(middle));
    world.objects.push_back(std::make_shared<Sphere>(right));

    // The light source is white, shining from above and to the left:
    world.light = std::make_shared<PointLight>(Point(-10, 10, -10),
                                               Color(1, 1, 1));

    return world;
}

int main()
{
    auto world = create_world();
    Camera camera(HSIZE, VSIZE, std::numbers::pi / 3);
    camera.transform =
        view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

    auto canvas = render(camera, world);
    write_PPM_file(canvas, "3_spheres");
}
