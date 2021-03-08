#include <cmath>
#include <scene/Lighting.hpp>

Color lighting(const Material &surface_mat, const Light &source,
               const Point &illuminated, const Vector &eye,
               const Vector &surface_norm) {
  Color ambient, diffuse, specular;

  const auto EFFECTIVE_COLOR = surface_mat.color * source.intensity;

  const auto LIGHT_V = Vector(source.position - illuminated).normalize();

  ambient = EFFECTIVE_COLOR * surface_mat.ambient;

  const auto LIGHT_PROJECTION = dot(LIGHT_V, surface_norm);
  if (LIGHT_PROJECTION < 0)
    diffuse = specular = Color(0, 0, 0); // black
  else {
    diffuse = EFFECTIVE_COLOR * surface_mat.diffuse * LIGHT_PROJECTION;

    const auto REFLECTION_V = reflect(-LIGHT_V, surface_norm);

    const auto REFLECTION_PROJECTION = dot(REFLECTION_V, eye);
    if (REFLECTION_PROJECTION <= 0)
      specular = Color(0, 0, 0);
    else {
      const auto FACTOR = pow(REFLECTION_PROJECTION, surface_mat.shininess);
      specular = source.intensity * surface_mat.specular * FACTOR;
    }
  }

  return ambient + diffuse + specular;
}
