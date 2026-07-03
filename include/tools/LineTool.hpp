#ifndef LINE_TOOL_HPP
#define LINE_TOOL_HPP

#include "Tool.hpp"
#include "figures/Line.hpp"
#include <GL/freeglut_std.h>
#include <optional>

namespace tools {
class LineTool {
  struct NoClick {};

  struct FirstClick {
    std::size_t x, y;
  };

  std::variant<NoClick, FirstClick> click;

public:
  using Target = figures::Line;

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

  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    auto first = std::get_if<FirstClick>(&click);

    if (!first)
      return;

    visit(first->x, first->y);
  }
};

static_assert(Tool<LineTool>, "LineTool is a tool");

} // namespace tools

#endif
