#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Figure.hpp"

namespace figures {
struct Rectangle {
  std::size_t x0;
  std::size_t y0;
  std::size_t x1;
  std::size_t y1;

  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    for (auto x = x0; x <= x1; ++x)
      for (auto y = y0; y <= y1; ++y)
        visit(x, y);
  }
};

static_assert(Figure<Rectangle>, "A rectangle is a figure");
} // namespace figures

#endif
