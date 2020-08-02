#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
public:
  Color();
  Color(float r, float g, float b);

  bool operator==(const Color &rhs) const;

  Color operator+(const Color &rhs) const;
  Color operator-(const Color &rhs) const;

  float red;
  float green;
  float blue;
};

#endif
