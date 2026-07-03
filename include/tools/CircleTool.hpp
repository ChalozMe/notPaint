#ifndef CIRCLE_TOOL_HPP
#define CIRCLE_TOOL_HPP

#include "Tool.hpp"
#include "figures/Circle.hpp"
#include <GL/freeglut_std.h>
#include <cmath>
#include <optional>

namespace tools {
class CircleTool {
  struct NoClick {};

  struct FirstClick {
    std::size_t x, y;
  };

  std::variant<NoClick, FirstClick> click;

public:
  using Target = figures::Circle;

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

      return Target{first_click.x, first_click.y, radius, {255, 0, 0, 255}};
    }
  }

  template <std::invocable<std::size_t, std::size_t, Color> Visit>
  void visit_pixels(Visit&& visit) const {
    auto first = std::get_if<FirstClick>(&click);

    if (!first)
      return;

    visit(first->x, first->y, Colors::BLACK);
  }
};

static_assert(Tool<CircleTool>, "LineTool is a tool");

} // namespace tools

#endif
