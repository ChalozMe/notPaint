#ifndef SELECTOR_SELECTOR_HPP
#define SELECTOR_SELECTOR_HPP

#include "Color.hpp"
#include "shape/Shape.hpp"
#include "figure/Line.hpp"
#include <GL/freeglut_std.h>
#include <sys/select.h>
#include <algorithm>
#include <numeric>
#include <vector>

namespace selector {
template <figure::Figure... Fs>
class Selector {
  using Shape = shape::Shape<Fs...>;
  std::optional<std::size_t> select_idx;

public:
  void mouse(int button, int state, int x, int y, std::vector<Shape>& shapes) {
    if (state != GLUT_DOWN || button != GLUT_LEFT_BUTTON)
      return;

    select_idx = std::nullopt;
    for (std::size_t i = shapes.size(); i-- > 0;)
      if (shapes[i].is_clicked(x, y)) {
        select_idx = i;
        break;
      }
  }

  void draw(Renderer& r, const std::vector<Shape>& shapes) const {
    if (!select_idx)
      return;

    const Shape& shape = shapes.at(*select_idx);

    auto [min_x, min_y, max_x, max_y] = shape.bounding_box();
    auto cx = std::midpoint(min_x, max_x);
    auto cy = std::midpoint(min_y, max_y);

    std::array<std::pair<float, float>, 4> corners = {{
      {shape.transform(min_x, min_y, cx, cy)},
      {shape.transform(min_x, max_y, cx, cy)},
      {shape.transform(max_x, max_y, cx, cy)},
      {shape.transform(max_x, min_y, cx, cy)},
    }};

    for (auto&& [x, y] : corners) {
      x = std::clamp(x, 0.0f, static_cast<float>(r.get_width() - 1));
      y = std::clamp(y, 0.0f, static_cast<float>(r.get_height() - 1));
    }

    for (std::size_t idx = 0; idx < 4; idx++) {
      auto [x0, y0] = corners[idx];
      auto [x1, y1] = corners[(idx + 1) % 4];
      figure::Line(x0, y0, x1, y1)
        .visit_pixels([&](std::size_t x, std::size_t y) {
          if ((x + y) % 2 == 0)
            r[x, y] = Colors::BLACK;
        });
    }
  }
};
} // namespace selector

#endif
