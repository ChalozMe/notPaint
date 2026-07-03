#ifndef NOT_PAINT_HPP
#define NOT_PAINT_HPP

#include "Color.hpp"
#include "Renderer.hpp"
#include "figures/Figure.hpp"
#include "tools/Tool.hpp"
#include "tools/LineTool.hpp"
#include "tools/RectangleTool.hpp"
#include "tools/CircleTool.hpp"
#include "tools/CrossTool.hpp"

namespace shape {
template <figures::Figure... Fs>
struct Shape {
  figures::StaticFigure<Fs...> figure;
  Color color;

  void draw(Renderer& r) const {
    figure.visit_pixels([&](std::size_t x, std::size_t y) {
      if (x < r.get_width() && y < r.get_height())
        r[x, y] = color;
    });
  }
};

template <class Sf>
struct FromStaticFigureImpl;

template <class... Fs>
struct FromStaticFigureImpl<figures::StaticFigure<Fs...>> {
  using t = Shape<Fs...>;
};

template <class Sf>
using FromStaticFigure = FromStaticFigureImpl<Sf>::t;
} // namespace shape

using StaticTool = tools::StaticTool<
  tools::LineTool,
  tools::RectangleTool,
  tools::CircleTool,
  tools::CrossTool>;
using StaticFigure = StaticTool::StaticFigure;
using Shape = shape::FromStaticFigure<StaticFigure>;

class NotPaint {
  std::vector<Shape> shapes = {
    {figures::Rectangle{0, 0, 200, 200}, {Colors::RED}},
    {figures::Rectangle{20, 20, 50, 50}, {Colors::GREEN}},
    {figures::Rectangle{70, 70, 100, 100}, {Colors::BLUE}},
    {figures::Line{10, 10, 200, 150}, {Colors::BLACK}},
    {figures::Circle{200, 200, 50}, {Colors::BLACK}},
  };

  std::optional<StaticTool> tool = tools::CircleTool{};

public:
  NotPaint() = default;

  void display(Renderer& renderer) const {
    renderer.clear(Colors::WHITE);
    for (auto&& shape : shapes)
      shape.draw(renderer);

    if (tool)
      tool->visit_pixels([&](std::size_t x, std::size_t y) {
        Shape{figures::Cross{x, y, 5}, Colors::BLACK}.draw(renderer);
      });
  }

  void idle() {}

  void mouse(int button, int state, int x, int y) {
    if (!tool)
      return;

    if (auto figure = tool->mouse(button, state, x, y))
      shapes.emplace_back(Shape{std::move(*figure), Colors::BLACK});
  }

  void motion(int, int) {}

  void keyboard(unsigned char key, int, int) {
    switch (key) {
      case 27: // Escape key
        tool.reset();
        break;
      case 'l':
        tool = tools::LineTool{};
        break;
      case 'r':
        tool = tools::RectangleTool{};
        break;
      case 'c':
        tool = tools::CircleTool{};
        break;
      case 'x':
        tool = tools::CrossTool{};
        break;
    }
  }

  void special(int, int, int) {}
};

#endif
