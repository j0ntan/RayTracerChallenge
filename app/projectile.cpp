#include <cmath>
#include <iostream>
#include <primitives/Canvas.hpp>
#include <primitives/Point.hpp>
#include <primitives/Vector.hpp>

/* Note: We take the plane containing the x and y components as being the plane
 * in which we run into if we move forward in the z direction. */

struct Projectile {
  Point position;
  Vector velocity;
};

struct Environment {
  Vector wind;
  const Vector gravity{-0.04, 0, 0};
};

Projectile tick(const Environment &env, const Projectile &current) {
  const auto new_position = current.position + current.velocity;
  const auto new_velocity = current.velocity + env.gravity + env.wind;
  return Projectile{new_position, new_velocity};
}

std::ostream &operator<<(std::ostream &out, const Projectile &projectile) {
  out << "(x: " << projectile.position.x << ", y: " << projectile.position.y
      << ", z: " << projectile.position.z << ')';
  return out;
}

int main() {
  // Let's place a projectile from the ground with a strong upward velocity &
  // forward component, i.e. strong x- and z-value.
  const Point INIT_POS = {0, 0, 0};
  const Vector INIT_VELOCITY = {6.5, 0, 3.2};
  Projectile projectile{INIT_POS, INIT_VELOCITY};

  // Let's have the wind blowing in a direction up and to the right with
  // respect to the projectile, with a small component against the
  // projectile's forward direction.
  const Environment environment{{0.01, 0.1, -0.002}};

  const unsigned int WIDTH = 1280, HEIGHT = 720;
  Canvas canvas(WIDTH, HEIGHT);

  while (projectile.position.x >= 0) {
    const auto X = static_cast<unsigned>(std::round(projectile.position.z));
    const auto Y =
        static_cast<unsigned>(std::round(HEIGHT - 1 - projectile.position.x));
    if (X >= 0 && X < WIDTH && Y >= 0 && Y < HEIGHT)
      canvas.write(X, Y, Color(1, 0, 0));
    else
      std::cout << "Out of bounds! " << projectile << '\n';

    projectile = tick(environment, projectile);
  }

  canvas.to_ppm_file("projectile");
}
