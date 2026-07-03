#ifndef NOT_PAINT_HPP
#define NOT_PAINT_HPP

#include "Scene.hpp"
#include "Renderer.hpp"
#include "figures/Figure.hpp"
#include "tools/Tool.hpp"
#include "tools/LineTool.hpp"
#include "tools/RectangleTool.hpp"
#include "tools/CircleTool.hpp"

namespace shape {
template <figures::Figure... Fs>
class Shape {
  figures::StaticFigure<Fs...> figure;

public:
  constexpr Shape() = default;

  template <figures::Figure F>
    requires(!std::same_as<std::remove_cvref_t<F>, Shape>) &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  constexpr Shape(F&& f) : figure(std::forward<F>(f)) {}

  template <figures::Figure F, class... Args>
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

template <class Sf>
struct FromStaticFigureImpl;

template <class... Fs>
struct FromStaticFigureImpl<figures::StaticFigure<Fs...>> {
  using t = Shape<Fs...>;
};

template <class Sf>
using FromStaticFigure = FromStaticFigureImpl<Sf>::t;
} // namespace shape

using StaticTool =
  tools::StaticTool<tools::LineTool, tools::RectangleTool, tools::CircleTool>;
using StaticFigure = StaticTool::StaticFigure;
using Shape = shape::FromStaticFigure<StaticFigure>;

class NotPaint {
  mutable Renderer renderer{WIDTH, HEIGHT};
  std::vector<Shape> shapes = {
    figures::Rectangle{0, 0, 200, 200, Colors::RED},
    figures::Rectangle{20, 20, 50, 50, Colors::GREEN},
    figures::Rectangle{70, 70, 100, 100, Colors::BLUE},
    figures::Line{10, 10, 200, 150, Colors::BLACK},
    figures::Circle{200, 200, 50, Colors::BLACK},
  };

public:
  NotPaint() = default;

  void display() const {
    renderer.clear(Colors::WHITE);
    for (auto&& shape : shapes)
      shape.draw(renderer);
    renderer.send_to_gpu();
  }

  void idle() {}
};

#endif
