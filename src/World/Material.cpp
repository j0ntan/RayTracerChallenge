#include <World/Material.hpp>

Material::Material(const Material &material)
    : color{material.color}, ambient{material.ambient},
      diffuse{material.diffuse}, specular{material.specular},
      shininess{material.shininess}, pattern{nullptr},
      reflective{material.reflective}, transparency{material.transparency},
      refractive_index{material.refractive_index}
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
        transparency = rhs.transparency;
        refractive_index = rhs.refractive_index;
        pattern = nullptr;

        if (rhs.pattern)
        {
            pattern = rhs.pattern->clone();
        }
    }

    return *this;
}
