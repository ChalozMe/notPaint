#ifndef FIGURE_CIRCLE_HPP
#define FIGURE_CIRCLE_HPP

#include "Figure.hpp"
#include <algorithm>

namespace figure {
struct Circle {
  std::size_t cx;
  std::size_t cy;
  float radius;

  // TODO: This is O(n^2), there are some O(n) algortihms
  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    float fx0 = static_cast<float>(cx) - radius;
    float fy0 = static_cast<float>(cy) - radius;
    float fx1 = static_cast<float>(cx) + radius;
    float fy1 = static_cast<float>(cy) + radius;

    std::size_t x0 = static_cast<std::size_t>(std::max(fx0, 0.0f));
    std::size_t y0 = static_cast<std::size_t>(std::max(fy0, 0.0f));
    std::size_t x1 = static_cast<std::size_t>(std::max(fx1, 0.0f));
    std::size_t y1 = static_cast<std::size_t>(std::max(fy1, 0.0f));

    for (std::size_t x = x0; x <= x1; x++) {
      for (std::size_t y = y0; y <= y1; y++) {
        float dx = static_cast<float>(cx) - static_cast<float>(x);
        float dy = static_cast<float>(cy) - static_cast<float>(y);

        if (dx * dx + dy * dy <= radius * radius)
          visit(x, y);
      }
    }
  }
};

static_assert(Figure<Circle>, "Circle is a figure");
} // namespace figure

#endif
