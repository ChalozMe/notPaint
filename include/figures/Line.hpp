#ifndef LINE_HPP
#define LINE_HPP

#include "Figure.hpp"
#include <cmath>

namespace figures {
struct Line {
  std::size_t x0;
  std::size_t y0;
  std::size_t x1;
  std::size_t y1;

  //Bresenham's line algorithim
  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    std::ptrdiff_t x0 = static_cast<std::ptrdiff_t>(this->x0);
    std::ptrdiff_t y0 = static_cast<std::ptrdiff_t>(this->y0);
    std::ptrdiff_t x1 = static_cast<std::ptrdiff_t>(this->x1);
    std::ptrdiff_t y1 = static_cast<std::ptrdiff_t>(this->y1);

    std::ptrdiff_t dx = std::abs(x1 - x0);
    std::ptrdiff_t dy = std::abs(y1 - y0);

    std::ptrdiff_t sx = (x0 < x1) ? 1 : -1;
    std::ptrdiff_t sy = (y0 < y1) ? 1 : -1;

    std::ptrdiff_t err = dx - dy;

    while (true) {
      visit(x0, y0);

      if (x0 == x1 && y0 == y1)
        break;

      std::ptrdiff_t e2 = 2 * err;

      if (e2 > -dy) {
        err -= dy;
        x0 += sx;
      }

      if (e2 < dx) {
        err += dx;
        y0 += sy;
      }
    }
  }
};

static_assert(Figure<Line>, "A Line is a figure");
} // namespace figures

#endif
