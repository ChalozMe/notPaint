#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Figure.hpp"
#include "Color.hpp"

namespace figures {
struct Rectangle {
  std::size_t x0;
  std::size_t y0;
  std::size_t x1;
  std::size_t y1;
  Color color;

  void draw(Renderer& r) const {
    for (auto x = x0; x <= x1; ++x)
      for (auto y = y0; y <= y1; ++y)
        r[x, y] = color;
  }
};

static_assert(FigureLike<Rectangle>, "A rectangle is a figure");
} // namespace figures

#endif
