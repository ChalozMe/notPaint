#include "Scene.hpp"
#include "Renderer.hpp"
#include "figures/Figure.hpp"
#include "figures/Line.hpp"
#include "figures/Rectangle.hpp"
#include "figures/Circle.hpp"

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

class NotPaint {
  mutable Renderer renderer{WIDTH, HEIGHT};
  std::vector<Shape> shapes = {
    figures::Rectangle{0, 0, 200, 200, Colors::RED},
    figures::Rectangle{20, 20, 50, 50, Colors::GREEN},
    figures::Rectangle{70, 70, 100, 100, Colors::BLUE},
    figures::Line{10, 10, 200, 150, Colors::WHITE},
    figures::Circle{200, 200, 50, Colors::WHITE},
  };

public:
  NotPaint() = default;

  void display() const {
    renderer.clear(Colors::BLACK);
    for (auto&& shape : shapes)
      shape.draw(renderer);
    renderer.send_to_gpu();
  }

  void idle() {}
};

int main(int argc, char* argv[]) {
  play_scene<NotPaint>(argc, argv, "NotPaint");
}
