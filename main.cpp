#include "Window.hpp"
#include "figures/Figure.hpp"
#include "figures/Line.hpp"
#include "figures/Rectangle.hpp"
#include "figures/Circle.hpp"

#include <optional>
#include <print>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>
#include <sstream>

namespace figures {
template <Figure... Fs>
class Shape {
  figures::StaticFigure<Fs...> figure;

public:
  constexpr Shape() = default;

  template <Figure F>
    requires(!std::same_as<std::remove_cvref_t<F>, Shape>) &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  constexpr Shape(F&& f) : figure(std::forward<F>(f)) {}

  template <Figure F, class... Args>
    requires std::constructible_from<F, Args...> &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  explicit constexpr Shape(std::in_place_type_t<F>, Args&&... args) :
    figure(std::in_place_type<F>, std::forward<Args>(args)...) {}

  void draw(Renderer& r) const {
    figure.visit_pixels([&r](std::size_t x, std::size_t y, Color color) {
      if (x < r.get_width() && y < r.get_height())
        r[x, y] = color;
    });
  }
};
} // namespace figures

using Shape =
  figures::Shape<figures::Line, figures::Rectangle, figures::Circle>;

std::optional<Shape> parse_figure(std::istream& is) {
  std::string cmd;
  is >> cmd;

  if (cmd == "rect") {
    std::size_t x0, y0, x1, y1;
    if (is >> x0 >> y0 >> x1 >> y1)
      return figures::Rectangle{x0, y0, x1, y1, Colors::RED};
  } else if (cmd == "line") {
    std::size_t x1, y1, x2, y2;
    if (is >> x1 >> y1 >> x2 >> y2)
      return figures::Line{x1, y1, x2, y2, Colors::WHITE};
  } else if (cmd == "circle") {
    std::size_t cx, cy;
    float radius;
    if (is >> cx >> cy >> radius)
      return figures::Circle{cx, cy, radius, Colors::BLUE};
  }
  return std::nullopt;
}

int main() {
  auto window = Window::create(800, 600);
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  std::vector<Shape> shapes = {
    figures::Rectangle{0, 0, 200, 200, Colors::RED},
    figures::Rectangle{20, 20, 50, 50, Colors::GREEN},
    figures::Rectangle{70, 70, 100, 100, Colors::BLUE},
    figures::Line{10, 10, 200, 150, Colors::WHITE},
    figures::Circle{200, 200, 50, Colors::WHITE},
  };

  std::mutex figures_mutex;

  std::thread([&]() {
    std::string line;

    while (std::getline(std::cin, line)) {
      std::istringstream iss(line);
      if (auto figure = parse_figure(iss)) {
        std::scoped_lock lock(figures_mutex);
        shapes.emplace_back(std::move(*figure));
      }
    }
  }).detach();

  window->run([&](Renderer& r, GLFWwindow*) {
    r.clear(Colors::BLACK);

    std::scoped_lock lock(figures_mutex);
    for (auto&& shape : shapes)
      shape.draw(r);
  });
}
