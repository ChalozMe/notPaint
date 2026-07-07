#ifndef NOT_PAINT_HPP
#define NOT_PAINT_HPP

#include "tool/Tool.hpp"
#include "tool/Line.hpp"
#include "tool/Rectangle.hpp"
#include "tool/Circle.hpp"
#include "tool/Cross.hpp"
#include "tool/Polygon.hpp"
#include "shape/Shape.hpp"

using StaticTool = tool::StaticTool<
  tool::Line,
  tool::Rectangle,
  tool::Circle,
  tool::Cross,
  tool::Polygon>;
using StaticFigure = StaticTool::StaticFigure;
using Shape = shape::FromStaticFigure<StaticFigure>;

class NotPaint {
  std::vector<Shape> shapes = {
    {figure::Rectangle{0, 0, 200, 200},
     Colors::RED,
     100uz,
     100uz,
     -0.3f,
     1.3f,
     1.0f},
    {figure::Rectangle{20, 20, 50, 50}, Colors::GREEN},
    {figure::Rectangle{70, 70, 100, 100}, Colors::BLUE},
    {figure::Line{10, 10, 200, 150}, Colors::BLACK},
    {figure::Circle{200, 200, 50}, Colors::BLACK},
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
        tool = tool::Line{};
        break;
      case 'r':
        tool = tool::Rectangle{};
        break;
      case 'c':
        tool = tool::Circle{};
        break;
      case 'x':
        tool = tool::Cross{};
        break;
      case 'p':
        tool = tool::Polygon{};
        break;
    }
  }

  void special(int, int, int) {}
};

#endif
