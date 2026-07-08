#ifndef NOT_PAINT_HPP
#define NOT_PAINT_HPP

#include "tool/Line.hpp"
#include "tool/Rectangle.hpp"
#include "tool/Circle.hpp"
#include "tool/Cross.hpp"
#include "tool/Polygon.hpp"
#include "CanvasMouse.hpp"

class NotPaint {
  using AnyTool = CanvasMouse<
    Input<tool::Line, 'l'>,
    Input<tool::Rectangle, 'r'>,
    Input<tool::Circle, 'c'>,
    Input<tool::Cross, 'x'>,
    Input<tool::Polygon, 'p'>>;

  AnyTool tool;
  std::vector<AnyTool::Shape> shapes = {
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

public:
  NotPaint() = default;

  void display(Renderer& renderer) const {
    renderer.clear(Colors::WHITE);
    for (auto&& shape : shapes)
      shape.draw(renderer);

    tool.draw(renderer, shapes);
  }

  void idle() {}

  void mouse(int button, int state, int x, int y) {
    if (auto figure = tool.mouse(button, state, x, y, shapes))
      shapes.emplace_back(*figure);
  }

  void motion(int, int) {}

  void keyboard(unsigned char key, int, int) {
    tool.keyboard(key);
  }

  void special(int, int, int) {}
};

#endif
