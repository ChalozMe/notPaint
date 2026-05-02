#include "Window.hpp"
#include "figures/Line.hpp"
#include "figures/Rectangle.hpp"
#include <print>

static constexpr auto main_loop = [](Renderer& r, GLFWwindow*) {
  r.clear(Colors::BLACK);

  figures::Rectangle(0, 0, 200, 200, Colors::RED).draw(r);
  figures::Rectangle(20, 20, 50, 50, Colors::GREEN).draw(r);
  figures::Rectangle(70, 70, 100, 100, Colors::BLUE).draw(r);
  figures::Line(10, 10, 200, 150, Colors::WHITE).draw(r);
};

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  window->run(main_loop);
}

//testing
