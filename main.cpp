#include "Window.hpp"
#include "figures/Figure.hpp"
#include "figures/Line.hpp"

#include <vector>
#include <print>

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  std::vector<figures::Figure> scene;

  
  scene.emplace_back([]{
    figures::Line l{0, 0, 200, 0, Colors::RED};
    l.transform.translate(300, 200).rotate(0.5f).scale(1.5f, 1.5f);
    return l;
  }());

  scene.emplace_back([]{
    figures::Line l{0, 0, 200, 0, Colors::GREEN};
    l.transform.translate(300, 200).rotate(1.0f);
    return l;
  }());

  scene.emplace_back(figures::Line{0, 0, 200, 0, Colors::BLUE});

  scene.emplace_back([]{
    figures::Line l{0, 0, 0, 200, Colors::WHITE};
    l.transform.translate(300, 200);
    return l;
  }());

  window->run([&](Renderer& r, GLFWwindow*) {
    r.clear(Colors::BLACK);

    for (const auto& f : scene)
      f.draw(r);
  });
}
