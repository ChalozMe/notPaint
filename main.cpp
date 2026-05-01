#include "Window.hpp"
#include "figures/Line.hpp"
#include <print>

void draw_rect(
  Renderer& r,
  unsigned x0,
  unsigned y0,
  unsigned x1,
  unsigned y1,
  Color p
) {
  for (auto x = x0; x <= x1; ++x)
    for (auto y = y0; y <= y1; ++y)
      r[x, y] = p;
}

static constexpr auto main_loop = [](Renderer& r, GLFWwindow*) {
  r.clear(Colors::BLACK);

  //draw_rect(r, 0, 0, 200, 200, Colors::RED);
  //draw_rect(r, 20, 20, 50, 50, Colors::GREEN);
  //draw_rect(r, 70, 70, 100, 100, Colors::BLUE);
  
  figures::draw_line(r, 0, 0, 800, 800, Colors::RED);

};

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  window->run(main_loop);
}

//testing
