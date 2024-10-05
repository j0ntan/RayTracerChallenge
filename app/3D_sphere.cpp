#include <graphics/Canvas.hpp>
#include <math/Transformations.hpp>
#include <scene/Light.hpp>
#include <scene/Lighting.hpp>
#include <scene/Ray.hpp>
#include <scene/Sphere.hpp>
#include <utility>

struct Scene {
  const Point viewpoint;
  const Sphere object;
  const double wall_z_coordinate;
  const Light source;
};

double calculate_wall_size(const Scene &scene) {
  const auto DISTANCE_TO_SPHERE =
      (scene.object.ORIGIN - scene.viewpoint).magnitude();
  const auto DISTANCE_TO_WALL =
      (Point(0, 0, scene.wall_z_coordinate) - scene.viewpoint).magnitude();
  const double SHADOW_DIAMETER =
      (scene.object.RADIUS / DISTANCE_TO_SPHERE * DISTANCE_TO_WALL) *
      2;                         // based on similar triangles
  return 1.25 * SHADOW_DIAMETER; // make wall slightly larger than shadow
}

typedef std::vector<std::pair<Point, Color>> Pixels_t;

Pixels_t cast_rays(const Scene &scene, const Canvas &canvas) {
  Pixels_t pixels;

  const double WALL_SIZE = calculate_wall_size(scene);
  const double PIXEL_SIZE = WALL_SIZE / canvas.height;

  for (size_t y = 0; y < canvas.height; ++y) {
    const auto WORLD_Y = (WALL_SIZE / 2) - PIXEL_SIZE * y;
    for (size_t x = 0; x < canvas.width; ++x) {
      const auto WORLD_X = -(WALL_SIZE / 2) + PIXEL_SIZE * x;

      const Point POINT_ON_WALL(WORLD_X, WORLD_Y, scene.wall_z_coordinate);
      const Ray RAY(scene.viewpoint,
                    Vector(POINT_ON_WALL - scene.viewpoint).normalize());
      const auto INTERSECTIONS = scene.object.intersect(RAY);
      if (auto intersection = hit(INTERSECTIONS)) {
        const auto POINT_OF_INTERSECTION = position(RAY, intersection->time());
        const auto NORMAL_V =
            intersection->object().normal_at(POINT_OF_INTERSECTION);
        const auto EYE_V = -RAY.DIRECTION;
        const auto PIXEL_COLOR =
            lighting(scene.object.material, scene.source, POINT_OF_INTERSECTION,
                     EYE_V, NORMAL_V);
        pixels.push_back(std::make_pair(Point(x, y, 0), PIXEL_COLOR));
      }
    }
  }

  return pixels;
}

int main() {
  const size_t PIXELS_LENGTH = 200;
  Canvas canvas(PIXELS_LENGTH, PIXELS_LENGTH);

  // optional sphere transformations
  const auto SHRINK_ALONG_Y_AXIS = scale(1, 0.5, 1);
  const auto SHRINK_ALONG_X_AXIS = scale(0.5, 1, 1);
  const auto SHRINK_AND_ROTATE = rotate_z(PI / 4) * scale(0.5, 1, 1);
  const auto SHRINK_AND_SKEW = shear(1, 0, 0, 0, 0, 0) * scale(0.5, 1, 1);

  Sphere sphere;
  sphere.material.color = Color(0.5, 0, 0);
  sphere.material.specular = 1;
  sphere.material.ambient - 0.5;
  sphere.material.diffuse = 0.7;
  sphere.apply_transformation(IDENTITY);

  const Scene SCENE = {Point(0, 0, -5), sphere, 10,
                       Light(Point(-10, 10, -10), Color(1, 1, 1))};

  const auto PIXELS = cast_rays(SCENE, canvas);

  for (const auto &PIXEL : PIXELS)
    canvas.write(PIXEL.first.x(), PIXEL.first.y(), PIXEL.second);

  write_PPM(canvas, "3D_sphere");
}
