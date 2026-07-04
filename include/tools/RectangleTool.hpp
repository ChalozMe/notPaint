#ifndef RECTANGLE_TOOL_HPP
#define RECTANGLE_TOOL_HPP

#include "Tool.hpp"
#include "figures/Cross.hpp"
#include "figures/Rectangle.hpp"
#include <GL/freeglut_std.h>

namespace tools {
class RectangleTool {
  struct NoClick {};

  struct FirstClick {
    std::size_t x, y;
  };

  std::variant<NoClick, FirstClick> click;

public:
  using Target = figures::Rectangle;

  std::optional<Target> mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN || button != GLUT_LEFT_BUTTON)
      return std::nullopt;

    if (std::holds_alternative<NoClick>(click)) {
      click =
        FirstClick{static_cast<std::size_t>(x), static_cast<std::size_t>(y)};
      return std::nullopt;
    } else {
      auto first_click = std::get<FirstClick>(click);
      click = NoClick{};

      return Target{
        first_click.x,
        first_click.y,
        static_cast<std::size_t>(x),
        static_cast<std::size_t>(y)
      };
    }
  }

  void draw(Renderer& renderer) const {
    auto first = std::get_if<FirstClick>(&click);

    if (!first)
      return;

    figures::Cross{first->x, first->y, 5.0f}.visit_pixels(
      [&](std::size_t x, std::size_t y) { renderer[x, y] = Colors::BLACK; }
    );
  }
};

static_assert(Tool<RectangleTool>, "RectangleTool is a tool");

} // namespace tools

#endif
