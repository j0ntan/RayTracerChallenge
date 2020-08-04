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
  const Vector gravity{-9, 0, 0};
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
  // Let's place a projectile with an altitude of 100 meters & velocity of 10
  // going forward, i.e. in the +z direction.
  const double INITIAL_ALTITUDE = 400;
  Projectile projectile{{INITIAL_ALTITUDE, 0, 0}, {0, 0, 10}};
  std::cout << "Projectile's initial position: " << projectile << "\n\n";

  // Let's have the wind blowing in a direction up and to the right with
  // respect to the projectile, with a small component against the
  // projectile's forward direction.
  const Environment environment{{2.5, 3.3, -0.2}};

  const unsigned int WIDTH = 1280, HEIGHT = 720;
  Canvas canvas(WIDTH, HEIGHT);

  std::size_t counter = 0;
  while (projectile.position.x > 0) {
    projectile = tick(environment, projectile);
    std::cout << "tick " << ++counter << ' ' << projectile << '\n';
  }

  std::cout << "\nThe projectile reached the ground after " << counter
            << " ticks.\n";
}
