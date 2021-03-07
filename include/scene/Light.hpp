#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <graphics/Color.hpp>
#include <math/Point.hpp>

class Light {
public:
  Light(const Point &position, const Color &intensity);
};

#endif
