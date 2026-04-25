#include "Window.hpp"
#include <print>

static constexpr auto main_loop = [](Renderer& r, GLFWwindow* window) {
  r.clear(Colors::BLACK);
  
  r.drawRect(0, 0, 200, 200, Colors::RED);
  r.drawRect(20, 20, 50, 50, Colors::GREEN);
  r.drawRect(70, 70, 100, 100, Colors::BLUE);
};

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  window->run(main_loop);
}
