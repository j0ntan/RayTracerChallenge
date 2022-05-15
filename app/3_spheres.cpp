#include <graphics/Camera.hpp>
#include <scene/Transformations.hpp>
#include <scene/View.hpp>

constexpr double CANVAS_SCALE = 10;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE, VSIZE = 50 * CANVAS_SCALE;

const auto HALF_PI = asin(1);
const auto QUARTER_PI = HALF_PI / 2;
const auto THIRD_PI = HALF_PI * (2.0 / 3);

World create_world() {
  World world;

  Sphere floor;
  floor.set_transformation(scale(10, 0.01, 10));
  Material floor_mat;
  floor_mat.color = Color{1, 0.9, 0.9};
  floor_mat.specular = 0;
  floor.set_material(floor_mat);

  Sphere left_wall;
  left_wall.set_transformation(translate(0, 0, 5) * rotate_y(-QUARTER_PI) *
                               rotate_x(HALF_PI) * scale(10, 0.01, 10));
  left_wall.set_material(floor_mat);

  Sphere right_wall;
  right_wall.set_transformation(translate(0, 0, 5) * rotate_y(QUARTER_PI) *
                                rotate_x(HALF_PI) * scale(10, 0.01, 10));
  right_wall.set_material(floor_mat);

  Sphere middle;
  middle.set_transformation(translate(-0.5, 1, 0.5));
  Material middle_mat;
  middle_mat.color = Color{0.1, 1, 0.5};
  middle_mat.diffuse = 0.7;
  middle_mat.specular = 0.3;
  middle.set_material(middle_mat);

  Sphere right;
  right.set_transformation(translate(1.5, 0.5, -0.5) * scale(0.5, 0.5, 0.5));
  Material right_mat;
  right_mat.color = Color{0.5, 1, 0.1};
  right_mat.diffuse = 0.7;
  right_mat.specular = 0.3;
  right.set_material(right_mat);

  Sphere left;
  left.set_transformation(translate(-1.5, 0.33, -0.75) *
                          scale(0.33, 0.33, 0.33));
  Material left_mat;
  left_mat.color = Color{1, 0.8, 0.1};
  left_mat.diffuse = 0.7;
  left_mat.specular = 0.3;
  left.set_material(left_mat);

  Light light(Point(-10, 10, -10), Color(1, 1, 1));

  world.add_sphere(floor);
  world.add_sphere(left_wall);
  world.add_sphere(right_wall);
  world.add_sphere(left);
  world.add_sphere(middle);
  world.add_sphere(right);
  world.add_light_source(light);

  return world;
}

int main() {
  auto world = create_world();
  Camera camera(HSIZE, VSIZE, THIRD_PI);
  camera.transform =
      view_transform(Point{0, 1.5, -5}, Point{0, 1, 0}, Vector{0, 1, 0});

  auto canvas = render(camera, world);
  canvas.write_PPM("3_spheres", MagicIdentifier::BINARY);
}
