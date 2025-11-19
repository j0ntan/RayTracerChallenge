#include <World/Material.hpp>

Material::Material(const Material &material)
    : color{material.color}, ambient{material.ambient},
      diffuse{material.diffuse}, specular{material.specular},
      shininess{material.shininess}, pattern{nullptr},
      reflective{material.reflective}
{
    if (material.pattern)
    {
        pattern = material.pattern->clone();
    }
}

Material &Material::operator=(const Material &rhs)
{
    if (this != &rhs)
    {
        color = rhs.color;
        ambient = rhs.ambient;
        diffuse = rhs.diffuse;
        specular = rhs.specular;
        shininess = rhs.shininess;
        reflective = rhs.reflective;
        pattern = nullptr;

        if (rhs.pattern)
        {
            pattern = rhs.pattern->clone();
        }
    }

    return *this;
}
