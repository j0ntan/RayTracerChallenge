#include <scene/Light.hpp>

Light::Light(const Point &position, const Color &intensity)
    : POSITION{position}, INTENSITY{intensity} {}
