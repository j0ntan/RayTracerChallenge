#ifndef VIEW_HPP
#define VIEW_HPP

#include <math/Point.hpp>
#include <math/Vector.hpp>

Matrix<4> view_transform(const Point &from, const Point &to, const Vector &up);

#endif
