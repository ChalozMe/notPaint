#include "Window.hpp"
#include "figures/Figure.hpp"
#include "figures/Line.hpp"
#include "figures/Rectangle.hpp"
#include <print>

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  std::vector<figures::Figure> figures = {
    figures::Rectangle(0, 0, 200, 200, Colors::RED),
    figures::Rectangle(20, 20, 50, 50, Colors::GREEN),
    figures::Rectangle(70, 70, 100, 100, Colors::BLUE),
    figures::Line(10, 10, 200, 150, Colors::WHITE),
  };

  window->run([&figures](Renderer& r, GLFWwindow*) {
    r.clear(Colors::BLACK);
    for (auto&& figure : figures)
      figure.draw(r);
  });
}

//testing
