#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
public:
  Color();
  Color(float r, float g, float b);

  bool operator==(const Color &rhs) const;

  const float red;
  const float green;
  const float blue;
};

#endif
