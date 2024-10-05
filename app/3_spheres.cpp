#include <graphics/Camera.hpp>
#include <math/Transformations.hpp>
#include <scene/View.hpp>

constexpr double CANVAS_SCALE = 10;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE, VSIZE = 50 * CANVAS_SCALE;

const auto HALF_PI = asin(1);
const auto QUARTER_PI = HALF_PI / 2;
const auto THIRD_PI = HALF_PI * (2.0 / 3);

World create_world() {
  World world;

  Sphere floor;
  floor.apply_transformation(scale(10, 0.01, 10));
  floor.material.color = Color{1, 0.9, 0.9};
  floor.material.specular = 0;

  Sphere left_wall;
  left_wall.apply_transformation(translate(0, 0, 5) * rotate_y(-QUARTER_PI) *
                                 rotate_x(HALF_PI) * scale(10, 0.01, 10));
  left_wall.material = floor.material;

  Sphere right_wall;
  right_wall.apply_transformation(translate(0, 0, 5) * rotate_y(QUARTER_PI) *
                                  rotate_x(HALF_PI) * scale(10, 0.01, 10));
  right_wall.material = floor.material;

  Sphere middle;
  middle.apply_transformation(translate(-0.5, 1, 0.5));
  middle.material.color = Color{0.1, 1, 0.5};
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;

  Sphere right;
  right.apply_transformation(translate(1.5, 0.5, -0.5) * scale(0.5, 0.5, 0.5));
  right.material.color = Color{0.5, 1, 0.1};
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;

  Sphere left;
  left.apply_transformation(translate(-1.5, 0.33, -0.75) *
                            scale(0.33, 0.33, 0.33));
  left.material.color = Color{1, 0.8, 0.1};
  left.material.diffuse = 0.7;
  left.material.specular = 0.3;

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
  write_PPM(canvas, "3_spheres");
}
