#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <algorithm>
#include <array>

template <std::size_t n = 0> struct Tuple {
  Tuple() = default;
  Tuple(const std::initializer_list<double> &list) {
    std::copy(list.begin(), list.begin() + (n <= list.size() ? n : list.size()),
              elements.begin());
  }
  Tuple(const std::array<double, n> &array) { elements = array; }

  std::array<double, n> elements;
  const std::size_t &size = elements.size();
};

#endif
