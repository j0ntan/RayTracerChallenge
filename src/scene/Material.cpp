#include <scene/Material.hpp>
#include <utility/Float_compare.hpp>

bool operator==(const Material &lhs, const Material &rhs) {
  return lhs.color == rhs.color && float_equals(lhs.ambient, rhs.ambient) &&
         float_equals(lhs.diffuse, rhs.diffuse) &&
         float_equals(lhs.specular, rhs.specular) &&
         float_equals(lhs.shininess, rhs.shininess);
}

bool operator!=(const Material &lhs, const Material &rhs) {
  return !(lhs == rhs);
}
