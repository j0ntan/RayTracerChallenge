#include <numbers>
#include <cmath>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>
#include <Math/Plane.hpp>
#include <Graphics/StripePattern.hpp>
#include <Graphics/RingPattern.hpp>
#include <World/Camera.hpp>
#include "PerlinNoise.hpp"

/**
 * @brief Canvas parameters for rendering the scene
 *
 */
constexpr double CANVAS_SCALE = 14;
constexpr std::size_t HSIZE = 100 * CANVAS_SCALE,
                      VSIZE = 50 * CANVAS_SCALE;

/**
 * @brief A radial gradient pattern that transitions between two colors in a
 *  ring
 *
 */
struct RingGradientPattern final : public Pattern
{
    Color a;
    Color b;

    RingGradientPattern(const Color &a, const Color &b) : a{a}, b{b}
    {
    }

    virtual ~RingGradientPattern() = default;

    std::unique_ptr<Pattern> clone() const override
    {
        return std::make_unique<RingGradientPattern>(*this);
    }

    Color pattern_at(const Point &point) const override
    {
        auto distance = b - a;
        auto P_x = point.x(), P_z = point.z();
        auto D = std::sqrt(P_x * P_x + P_z * P_z);
        auto fraction = D - std::floor(D);

        return a + distance * fraction;
    }
};

/**
 * @brief A pattern that blends two patterns together by averaging their colors
 *
 */
struct BlendedPattern : public Pattern
{
    std::unique_ptr<Pattern> p1, p2;

    BlendedPattern(const Pattern &a, const Pattern &b)
        : p1{a.clone()}, p2{b.clone()}
    {
    }

    BlendedPattern(const BlendedPattern &other)
        : p1{other.p1->clone()}, p2{other.p2->clone()}
    {
    }

    BlendedPattern(BlendedPattern &&other) = default;

    BlendedPattern &operator=(const BlendedPattern &rhs)
    {
        if (this != &rhs)
        {
            p1 = rhs.p1->clone();
            p2 = rhs.p2->clone();
        }

        return *this;
    }

    BlendedPattern &operator=(BlendedPattern &&rhs) = default;

    virtual ~BlendedPattern() = default;

    std::unique_ptr<Pattern> clone() const override
    {
        return std::make_unique<BlendedPattern>(*this);
    }

    Color pattern_at(const Point &point) const override
    {
        auto p1_color = p1->pattern_at(inverse(p1->transform) * point);
        auto p2_color = p2->pattern_at(inverse(p2->transform) * point);
        return (p1_color + p2_color) * (1.0 / 2.0);
    }
};

/**
 * @brief A pattern that perturbs the input point using Perlin noise before
 * querying a sub-pattern
 *
 */
struct PerturbPattern final : public Pattern
{
    const siv::PerlinNoise x_perlin{123456u};
    const siv::PerlinNoise y_perlin{123457u};
    const siv::PerlinNoise z_perlin{123458u};
    std::unique_ptr<Pattern> subpattern;

    PerturbPattern(const Pattern &pattern)
        : Pattern(pattern), subpattern{pattern.clone()}
    {
    }

    PerturbPattern(const PerturbPattern &other) : subpattern{}
    {
        if (other.subpattern)
        {
            subpattern = other.subpattern->clone();
            transform = subpattern->transform;
        }
    }

    PerturbPattern(PerturbPattern &&other) = default;

    PerturbPattern &operator=(const PerturbPattern &rhs)
    {
        if (this != &rhs)
        {
            subpattern = rhs.subpattern ? rhs.subpattern->clone() : nullptr;
            transform = subpattern->transform;
        }

        return *this;
    }

    PerturbPattern &operator=(PerturbPattern &&rhs) = default;

    virtual ~PerturbPattern() = default;

    std::unique_ptr<Pattern> clone() const override
    {
        return std::make_unique<PerturbPattern>(*this);
    }

    Color pattern_at(const Point &point) const override
    {
        auto octaves = 5;
        auto x_noise = x_perlin.octave3D_11(point.x(), point.y(), point.z(),
                                            octaves);
        auto x_perturbed = point.x() + x_noise;
        auto y_noise = y_perlin.octave3D_11(point.x(), point.y(), point.z(),
                                            octaves);
        auto y_perturbed = point.y() + y_noise;
        auto z_noise = z_perlin.octave3D_11(point.x(), point.y(), point.z(),
                                            octaves);
        auto z_perturbed = point.z() + z_noise;
        auto perturbed_point = Point(x_perturbed, y_perturbed, z_perturbed);

        return subpattern->pattern_at(perturbed_point);
    }
};

/**
 * @brief Create the world according to the book's description.
 *
 * @return World The specified world
 */
World create_world()
{
    // create patterns to be used in the world
    RingGradientPattern rgp(Color(1, 0, 0), Color(0, 0, 1));

    StripePattern h_stripe{Color(0, 0, 0), Color(1, 1, 1)};
    StripePattern v_stripe{Color(1, 0, 0), Color(0, 0, 1)};
    v_stripe.transform = rotation_y(std::numbers::pi / 2);
    BlendedPattern blended(h_stripe, v_stripe);

    h_stripe.transform = scaling(0.3, 0.3, 0.3);
    PerturbPattern perturb(h_stripe);

    World world;

    Plane floor;
    floor.material = Material();
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;
    floor.material.pattern = std::make_unique<StripePattern>(v_stripe);

    // The large sphere in the middle is a unit sphere, translated upward
    // slightly and colored green.
    Sphere middle_sphere;
    middle_sphere.transform = translation(-0.5, 1, 0.5);
    middle_sphere.material = Material();
    middle_sphere.material.color = Color(0.1, 1, 0.5);
    middle_sphere.material.diffuse = 0.7;
    middle_sphere.material.specular = 0.3;
    middle_sphere.material.pattern = std::make_unique<PerturbPattern>(perturb);

    world.objects.push_back(std::make_shared<Plane>(floor));
    world.objects.push_back(std::make_shared<Sphere>(middle_sphere));

    // The light source is white, shining from above and to the left:
    world.light = std::make_shared<PointLight>(Point(-1.4, 2, -2),
                                               Color(1, 1, 1));

    return world;
}

int main()
{
    auto world = create_world();
    Camera camera(HSIZE, VSIZE, 140 * std::numbers::pi / 180);

    // place camera in corner in the 4th quadrant in xz-plane, facing center
    camera.transform = view_transform(
        Point(0, 1.6, -1.6),
        Point(0, 0.4, -0.8),
        Vector(0, 1, 0));

    auto canvas = render(camera, world);
    write_PPM_file(canvas, "radial_gradient_pattern");
}
