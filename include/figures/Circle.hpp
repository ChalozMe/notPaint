#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <algorithm>
#include "Figure.hpp"
#include "Color.hpp"

namespace figures {
struct Circle {
  std::size_t cx;
  std::size_t cy;
  float radius;
  Color color;

  // TODO: This is O(n^2), there are some O(n) algortihms
  void draw(Renderer& r) const {
    float fx0 = static_cast<float>(cx) - radius;
    float fy0 = static_cast<float>(cy) - radius;
    float fx1 = static_cast<float>(cx) + radius;
    float fy1 = static_cast<float>(cy) + radius;

    float fxmax = static_cast<float>(r.get_width() - 1);
    float fymax = static_cast<float>(r.get_height() - 1);

    std::size_t x0 = static_cast<std::size_t>(std::clamp(fx0, 0.0f, fxmax));
    std::size_t y0 = static_cast<std::size_t>(std::clamp(fy0, 0.0f, fymax));
    std::size_t x1 = static_cast<std::size_t>(std::clamp(fx1, 0.0f, fxmax));
    std::size_t y1 = static_cast<std::size_t>(std::clamp(fy1, 0.0f, fymax));

    for (std::size_t x = x0; x <= x1; x++) {
      for (std::size_t y = y0; y <= y1; y++) {
        float dx = static_cast<float>(cx) - static_cast<float>(x);
        float dy = static_cast<float>(cy) - static_cast<float>(y);

        if (dx * dx + dy * dy <= radius * radius)
          r[x, y] = color;
      }
    }
  }
};

static_assert(Figure<Circle>, "A circle is a figure");
} // namespace figures

#endif
