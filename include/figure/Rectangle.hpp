#ifndef FIGURE_RECTANGLE_HPP
#define FIGURE_RECTANGLE_HPP

#include "Figure.hpp"
#include <algorithm>

namespace figure {
struct Rectangle {
  std::size_t x0;
  std::size_t y0;
  std::size_t x1;
  std::size_t y1;

  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    for (auto x = std::min(x0, x1); x <= std::max(x1, x0); ++x)
      for (auto y = std::min(y0, y1); y <= std::max(y1, y0); ++y)
        visit(x, y);
  }
};

static_assert(Figure<Rectangle>, "Rectangle is a figure");
} // namespace figure

#endif
