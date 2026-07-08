#ifndef TOOL_CIRCLE_HPP
#define TOOL_CIRCLE_HPP

#include "Tool.hpp"
#include "figure/Circle.hpp"
#include "figure/Cross.hpp"
#include <GL/freeglut_std.h>
#include <cmath>

namespace tool {
class Circle {
  struct NoClick {};

  struct FirstClick {
    std::size_t x, y;
  };

  std::variant<NoClick, FirstClick> click;

public:
  using Target = figure::Circle;

  std::optional<Target> mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN || button != GLUT_LEFT_BUTTON)
      return std::nullopt;

    if (std::holds_alternative<NoClick>(click)) {
      click =
        FirstClick{static_cast<std::size_t>(x), static_cast<std::size_t>(y)};
      return std::nullopt;
    } else {
      auto first_click = std::get<FirstClick>(click);
      float radius = std::hypot<float>(
        static_cast<float>(first_click.x) - x,
        static_cast<float>(first_click.y) - y
      );
      click = NoClick{};

      return Target{first_click.x, first_click.y, radius};
    }
  }

  void draw(Renderer& renderer) const {
    auto first = std::get_if<FirstClick>(&click);

    if (!first)
      return;

    figure::Cross{first->x, first->y, 5.0f}.visit_pixels(
      [&](std::size_t x, std::size_t y) { renderer[x, y] = Colors::BLACK; }
    );
  }
};

static_assert(Tool<Circle>, "CircleTool is a tool");
} // namespace tool

#endif
