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

std::optional<figures::Figure> parse_figure(std::istream& iss) {
  std::string cmd;
  iss >> cmd;

  if (cmd == "rect") {
    int x, y, w, h;
    if (iss >> x >> y >> w >> h)
      return figures::Rectangle(x, y, w, h, Colors::RED);
  } else if (cmd == "line") {
    int x1, y1, x2, y2;
    if (iss >> x1 >> y1 >> x2 >> y2)
      return figures::Line(x1, y1, x2, y2, Colors::WHITE);
  } else if (cmd == "circle") {
    int cx, cy;
    float radius;
    if (iss >> cx >> cy >> radius)
      return figures::Circle(cx, cy, radius, Colors::BLUE);
  }
  return std::nullopt;
}

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

  std::mutex figures_mutex;

  std::thread([&]() {
    std::string line;

    while (std::getline(std::cin, line)) {
      std::istringstream iss(line);
      if (auto figure = parse_figure(iss)) {
        std::scoped_lock lock(figures_mutex);
        figures.emplace_back(std::move(*figure));
      }
    }
  }).detach();

  window->run([&](Renderer& r, GLFWwindow*) {
    r.clear(Colors::BLACK);

    std::scoped_lock lock(figures_mutex);
    for (auto&& figure : figures)
      figure.draw(r);
  });
}
