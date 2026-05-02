#ifndef LINE_HPP
#define LINE_HPP

#include "Figure.hpp"
#include "graphics/Color.hpp"
#include "core/Vec2.hpp"
#include "transform/Transform2D.hpp"

#include <cstdlib>

namespace figures {

struct Line {
  Vec2 p0;
  Vec2 p1;
  Color color;
  Transform2D transform{};

  void draw(Renderer& r) const {
    // apply transform
    Vec2 a = transform.apply(p0);
    Vec2 b = transform.apply(p1);

    int x0 = (int)a.x;
    int y0 = (int)a.y;
    int x1 = (int)b.x;
    int y1 = (int)b.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true) {
      if (x0 >= 0 && y0 >= 0 &&
          x0 < (int)r.get_width() &&
          y0 < (int)r.get_height()) {
        r[x0, y0] = color;
      }

      if (x0 == x1 && y0 == y1)
        break;

      int e2 = 2 * err;

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

static_assert(FigureLike<Line>, "Line must satisfy FigureLike");

} // namespace figures

#endif
