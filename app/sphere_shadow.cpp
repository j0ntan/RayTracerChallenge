#include <graphics/Canvas.hpp>
#include <math/Intersections.hpp>
#include <math/Ray.hpp>
#include <math/Sphere.hpp>
#include <math/Transformations.hpp>

struct Scene {
  const Point viewpoint;
  const Sphere object;
  const double wall_z_coordinate;
};

double calculate_wall_size(const Scene &scene) {
  const auto DISTANCE_TO_SPHERE =
      (scene.object.origin() - scene.viewpoint).magnitude();
  const auto DISTANCE_TO_WALL =
      (Point(0, 0, scene.wall_z_coordinate) - scene.viewpoint).magnitude();
  const double SHADOW_DIAMETER =
      (scene.object.radius() / DISTANCE_TO_SPHERE * DISTANCE_TO_WALL) * 2;
  return 1.25 * SHADOW_DIAMETER; // make wall slightly larger than shadow
}

std::vector<Point> cast_rays(const Scene &scene, const Canvas &canvas) {
  std::vector<Point> points;

  const double WALL_SIZE = calculate_wall_size(scene);
  const double PIXEL_SIZE = WALL_SIZE / canvas.height;

  for (size_t y = 0; y < canvas.height; ++y) {
    const auto WORLD_Y = (WALL_SIZE / 2) - PIXEL_SIZE * y;
    for (size_t x = 0; x < canvas.width; ++x) {
      const auto WORLD_X = -(WALL_SIZE / 2) + PIXEL_SIZE * x;

      const Point POINT_ON_WALL(WORLD_X, WORLD_Y, scene.wall_z_coordinate);
      const Ray RAY(scene.viewpoint,
                    Vector(POINT_ON_WALL - scene.viewpoint).normalize());
      const auto INTERSECTIONS = intersect(scene.object, RAY);
      if (hit(INTERSECTIONS))
        points.push_back(Point(x, y, 0));
    }
  }

  return points;
}

int main() {
  const unsigned int PIXELS_LENGTH = 200;
  Canvas canvas(PIXELS_LENGTH, PIXELS_LENGTH);

  // optional sphere transformations
  const auto SHRINK_ALONG_Y_AXIS = scale(1, 0.5, 1);
  const auto SHRINK_ALONG_X_AXIS = scale(0.5, 1, 1);
  const auto SHRINK_AND_ROTATE = rotate_z(PI / 4) * scale(0.5, 1, 1);
  const auto SHRINK_AND_SKEW = shear(1, 0, 0, 0, 0, 0) * scale(0.5, 1, 1);

  Sphere sphere;
  sphere.set_transformation(identity);

  const Scene SCENE = {Point(0, 0, -5), sphere, 10};

  const auto POINTS = cast_rays(SCENE, canvas);

  for (const auto &POINT : POINTS)
    canvas.write(POINT.x(), POINT.y(), Color(.5, 0, 0)); // use red color

  canvas.to_ppm_file("shadow");
}
