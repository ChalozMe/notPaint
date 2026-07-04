#ifndef POLYGON_TOOL_HPP
#define POLYGON_TOOL_HPP

#include "Tool.hpp"
#include "figures/Cross.hpp"
#include "figures/Line.hpp"
#include "figures/Polygon.hpp"
#include <GL/freeglut_std.h>

namespace tools {
class PolygonTool {
  std::vector<std::pair<std::size_t, std::size_t>> points;

public:
  using Target = figures::Polygon;

  std::optional<Target> mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN)
      return std::nullopt;

    if (button == GLUT_LEFT_BUTTON) {
      points.push_back({x, y});
      return std::nullopt;
    }

    if (button != GLUT_RIGHT_BUTTON)
      return std::nullopt;

    if (points.size() < 3) {
      return std::nullopt;
    } else {
      points.push_back(points[0]);
      return Target{std::exchange(
        points,
        std::vector<std::pair<std::size_t, std::size_t>>()
      )};
    }
  }

  void draw(Renderer& renderer) const {
    auto drawer = [&](std::size_t x, std::size_t y) {
      renderer[x, y] = Colors::BLACK;
    };

    for (auto [x, y] : points)
      figures::Cross{x, y, 5.0f}.visit_pixels(drawer);

    for (auto [p0, p1] : std::views::pairwise(points)) {
      auto [x0, y0] = p0;
      auto [x1, y1] = p1;

      figures::Line{x0, y0, x1, y1}.visit_pixels(drawer);
    }
  }
};

static_assert(Tool<PolygonTool>, "PolygonTool is a tool");

} // namespace tools

#endif
