#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <graphics/Color.hpp>

struct Material {
  Color color = Color(1, 1, 1);
  double ambient = 0.1;
  double diffuse = 0.9;
  double specular = 0.9;
  double shininess = 200;
};

#endif
