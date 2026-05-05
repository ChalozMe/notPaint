#ifndef LINE_HPP
#define LINE_HPP

#include "Figure.hpp"
#include "Color.hpp"

#include <cstdlib>
#include <cstddef>

namespace figures {
// r.width() >= x1 >= x0
// r.height() >= y1 >= y0
struct Line {
  std::size_t x0;
  std::size_t y0;
  std::size_t x1;
  std::size_t y1;
  Color color;

  //Bresenham's line algorithim
  void draw(Renderer& r) const {
    std::ptrdiff_t dx = x1 - x0;
    std::ptrdiff_t dy = y1 - y0;

    std::ptrdiff_t delta = 2 * dy - dx;

    std::size_t y = y0;
    for (std::size_t x = x0; x <= x1; x++) {
      r[x, y] = color;
      if (delta > 0) {
        y++;
        delta += 2 * (dy - dx);
      } else {
        delta += 2 * dy;
      }
    }
  }
};

static_assert(FigureLike<Line>, "A rectangle is a figure");
} // namespace figures

#endif
