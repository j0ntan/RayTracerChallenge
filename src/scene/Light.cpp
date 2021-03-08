#include <scene/Light.hpp>

Light::Light(const Point &position, const Color &intensity)
    : position{position}, intensity{intensity} {}
