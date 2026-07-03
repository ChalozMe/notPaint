#ifndef CROSS_HPP
#define CROSS_HPP

#include "figures/Line.hpp"
#include <algorithm>

namespace figures {
struct Cross {
  std::size_t cx;
  std::size_t cy;
  float radius;

  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    static constexpr float sqrt2_2 = 0.707f;
    float dist = radius * sqrt2_2;

    std::size_t min_x = std::max(cx - dist, 0.0f);
    std::size_t max_x = cx + dist;
    std::size_t min_y = std::max(cy - dist, 0.0f);
    std::size_t max_y = cy + dist;

    Line{cx, cy, min_x, min_y}.visit_pixels(std::forward<Visit>(visit));
    Line{cx, cy, min_x, max_y}.visit_pixels(std::forward<Visit>(visit));
    Line{cx, cy, max_x, min_y}.visit_pixels(std::forward<Visit>(visit));
    Line{cx, cy, max_x, max_y}.visit_pixels(std::forward<Visit>(visit));
  }
};

static_assert(Figure<Cross>, "A circle is a figure");
} // namespace figures

#endif
