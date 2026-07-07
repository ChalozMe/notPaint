#ifndef NOT_PAINT_HPP
#define NOT_PAINT_HPP

#include "tools/Tool.hpp"
#include "tools/Line.hpp"
#include "tools/Rectangle.hpp"
#include "tools/Circle.hpp"
#include "tools/Cross.hpp"
#include "tools/Polygon.hpp"
#include "shape/Shape.hpp"

using StaticTool = tools::StaticTool<
  tools::Line,
  tools::Rectangle,
  tools::Circle,
  tools::Cross,
  tools::Polygon>;
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

  std::optional<StaticTool> tool;

public:
  NotPaint() = default;

  void display(Renderer& renderer) const {
    renderer.clear(Colors::WHITE);
    for (auto&& shape : shapes)
      shape.draw(renderer);

    if (tool)
      tool->draw(renderer);
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
        tool = tools::Line{};
        break;
      case 'r':
        tool = tools::Rectangle{};
        break;
      case 'c':
        tool = tools::Circle{};
        break;
      case 'x':
        tool = tools::Cross{};
        break;
      case 'p':
        tool = tools::Polygon{};
        break;
    }
  }

  void special(int, int, int) {}
};

#endif
