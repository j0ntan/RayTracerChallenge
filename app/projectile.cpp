#include <iostream>
#include <cmath>
#include <Math/Vector.hpp>
#include <Graphics/Canvas.hpp>

/* Note: We define the projectile's upward & forward directions as an x- and
 * z-component, respectively.
 */

struct Projectile
{
    Point position;
    Vector velocity;
};

struct Environment
{
    Vector wind;
    const Vector gravity{-0.04, 0, 0};
};

Projectile tick(const Environment &env, const Projectile &current)
{
    const auto new_position = current.position + current.velocity;
    const auto new_velocity = current.velocity + env.gravity + env.wind;
    return Projectile{new_position, new_velocity};
}

std::ostream &operator<<(std::ostream &out, const Projectile &projectile)
{
    out << "(x: " << projectile.position.x()
        << ", y: " << projectile.position.y()
        << ", z: " << projectile.position.z() << ')';
    return out;
}

int main()
{
    // Let's place a projectile from the ground with a strong upward velocity &
    // forward component, i.e. strong x- and z-value.
    Projectile projectile{{0, 0, 0}, {6.5, 0, 3.2}};

    // Let's have the wind blowing in a direction up and to the right with
    // respect to the projectile, with a small component against the
    // projectile's forward direction.
    const Environment environment{{0.01, 0, -0.002}};

    const size_t WIDTH = 1280, HEIGHT = 720;
    Canvas canvas(WIDTH, HEIGHT);

    do
    {
        const auto X = static_cast<unsigned>(
            std::round(projectile.position.z()));
        const auto Y = static_cast<unsigned>(
            std::round(HEIGHT - 1 - projectile.position.x()));

        if (X >= 0 && X < WIDTH && Y >= 0 && Y < HEIGHT)
        {
            canvas.write_pixel(X, Y, Color(1, 0, 0));
        }
        else
        {
            std::cout << "Out of bounds! " << projectile << '\n';
        }
    } while ((projectile = tick(environment, projectile)).position.x() >= 0);

    write_PPM_file(canvas, "projectile");
}
