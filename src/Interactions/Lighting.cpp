#include <cmath>
#include <Interactions/Lighting.hpp>

Color lighting(const Shape &object, const PointLight &light, const Point &point,
               const Vector eye_vector, const Vector &normal, bool in_shadow)
{
    Color color;
    if (object.material.pattern)
    {
        color = object.material.pattern->stripe_at_object(object, point);
    }
    else
    {
        color = object.material.color;
    }

    // combine the surface color with the light's color/intensity
    auto effective_color = color * light.intensity;

    // find the direction to the light source
    auto lightv = normalize(light.position - point);

    // compute the ambient contribution
    auto ambient = effective_color * object.material.ambient;

    // light_dot_normal represents the cosine of the angle between the
    // light vector and the normal vector. A negative number means the
    // light is on the other side of the surface.
    auto light_dot_normal = dot(lightv, normal);

    Color diffuse, specular;
    if (light_dot_normal < 0 || in_shadow)
    {
        diffuse = Color{};
        specular = Color{};
    }
    else
    {
        // compute the diffuse contribution
        diffuse = effective_color * object.material.diffuse * light_dot_normal;

        // reflect_dot_eye represents the cosine of the angle between the
        // reflection vector and the eye vector. A negative number means the
        // light reflects away from the eye.
        auto reflectv = reflect(-lightv, normal);
        auto reflect_dot_eye = dot(reflectv, eye_vector);
        if (reflect_dot_eye <= 0)
        {
            specular = Color{};
        }
        else
        {
            // compute the specular contribution
            auto factor = std::pow(reflect_dot_eye, object.material.shininess);
            specular = light.intensity * object.material.specular * factor;
        }
    }

    // # Add the three contributions together to get the final shading
    return ambient + diffuse + specular;
}
