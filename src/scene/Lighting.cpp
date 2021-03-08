#include <cmath>
#include <scene/Lighting.hpp>

Color lighting(const Material &surface_mat, const Light &source,
               const Point &illuminated, const Vector &eye,
               const Vector &surface_norm) {
  Color ambient, diffuse, specular; // defaulted to black

  const auto EFFECTIVE_COLOR = surface_mat.color * source.intensity;

  const auto LIGHT_V = Vector(source.position - illuminated).normalize();

  ambient = EFFECTIVE_COLOR * surface_mat.ambient;

  const auto LIGHT_PROJECTION = dot(LIGHT_V, surface_norm);
  if (LIGHT_PROJECTION >= 0) {
    diffuse = EFFECTIVE_COLOR * surface_mat.diffuse * LIGHT_PROJECTION;

    const auto REFLECTION_PROJECTION =
        dot(reflect(-LIGHT_V, surface_norm), eye);

    if (REFLECTION_PROJECTION > 0)
      specular = source.intensity * surface_mat.specular *
                 pow(REFLECTION_PROJECTION, surface_mat.shininess);
  }

  return ambient + diffuse + specular;
}
