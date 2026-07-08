#ifndef SELECTOR_SELECTOR_HPP
#define SELECTOR_SELECTOR_HPP

#include "Color.hpp"
#include "shape/Shape.hpp"
#include "figure/Line.hpp"
#include <GL/freeglut_std.h>
#include <numeric>
#include <optional>
#include <variant>
#include <vector>

namespace selector {
template <figure::Figure... Fs>
class Selector {
  using Shape = shape::Shape<Fs...>;

  struct Selection {};

  struct Dragging {
    int last_x;
    int last_y;
  };

  struct Interaction {
    std::size_t shape_idx;
    std::variant<Selection, Dragging> action;
  };

  std::optional<Interaction> interaction;

public:
  void mouse(int button, int state, int x, int y, std::vector<Shape>& shapes) {
    if (button != GLUT_LEFT_BUTTON)
      return;

    if (
      state == GLUT_DOWN && interaction &&
      std::holds_alternative<Selection>(interaction->action)
    ) {
      if (shapes.at(interaction->shape_idx).is_clicked(x, y))
        interaction->action = Dragging{x, y};
      else
        interaction.reset();
    } else if (
      state == GLUT_UP && std::holds_alternative<Dragging>(interaction->action)
    ) {
      interaction->action = Selection{};
    }

    if (state == GLUT_DOWN && !interaction) {
      for (std::size_t i = shapes.size(); i-- > 0;)
        if (shapes.at(i).is_clicked(x, y)) {
          interaction = {i, Dragging{x, y}};
          break;
        }
    }
  }

  void motion(int x, int y, std::vector<Shape>& shapes) {
    if (!interaction)
      return;

    Shape& shape = shapes.at(interaction->shape_idx);

    std::visit(
      [&]<class T>(T& state) {
        if constexpr (std::is_same_v<T, Dragging>) {
          shape.tx += static_cast<float>(x - state.last_x);
          shape.ty += static_cast<float>(y - state.last_y);

          state.last_x = x;
          state.last_y = y;
        }
      },
      interaction->action
    );
  }

  void draw(Renderer& r, const std::vector<Shape>& shapes) const {
    if (!interaction)
      return;

    const Shape& shape = shapes.at(interaction->shape_idx);

    auto [min_x, min_y, max_x, max_y] = shape.bounding_box();
    auto cx = std::midpoint(min_x, max_x);
    auto cy = std::midpoint(min_y, max_y);

    std::array<std::pair<float, float>, 4> corners = {{
      {shape.transform(min_x, min_y, cx, cy)},
      {shape.transform(min_x, max_y, cx, cy)},
      {shape.transform(max_x, max_y, cx, cy)},
      {shape.transform(max_x, min_y, cx, cy)},
    }};

    for (std::size_t idx = 0; idx < 4; idx++) {
      auto [x0, y0] = corners[idx];
      auto [x1, y1] = corners[(idx + 1) % 4];

      // TODO: cut the line so that it falls within boundaries
      // maybe Liang–Barsky algorithm, rn it just crashes lmao

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
