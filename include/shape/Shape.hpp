#ifndef SHAPE_SHAPE_HPP
#define SHAPE_SHAPE_HPP

#include "figure/Figure.hpp"
#include "Renderer.hpp"
#include <array>
#include <cmath>
#include <numeric>

namespace shape {
template <figure::Figure... Fs>
struct Shape {
  figure::StaticFigure<Fs...> figure;
  Color color;
  std::size_t tx = 0uz;
  std::size_t ty = 0uz;
  float sx = 1.0f;
  float sy = 1.0f;
  float angle = 0.0f;

  bool is_clicked(std::size_t x, std::size_t y) const {
    bool is_clicked = false;

    figure.visit_pixels([&](std::size_t _x, std::size_t _y) {
      is_clicked = is_clicked || (x == _x && y == _y);
    });

    return is_clicked;
  }

  std::array<std::size_t, 4> bounding_box() const {
    std::size_t min_x = -1, min_y = -1, max_x = 0, max_y = 0;

    figure.visit_pixels([&](std::size_t x, std::size_t y) {
      min_x = std::min(min_x, x);
      min_y = std::min(min_y, y);
      max_x = std::max(max_x, x);
      max_y = std::max(max_y, y);
    });

    return {min_x, min_y, max_x, max_y};
  }

  void draw(Renderer& r) const {
    auto [min_x, min_y, max_x, max_y] = bounding_box();
    auto cx = std::midpoint(min_x, max_x);
    auto cy = std::midpoint(min_y, max_y);

    figure.visit_pixels([&](std::size_t fx, std::size_t fy) {
      float dx = static_cast<float>(fx) - static_cast<float>(cx);
      float dy = static_cast<float>(fy) - static_cast<float>(cy);
      float rx = dx * std::cos(angle) - dy * std::sin(angle);
      float ry = dx * std::sin(angle) + dy * std::cos(angle);
      float x = sx * rx + static_cast<float>(cx);
      float y = sy * ry + static_cast<float>(cy);

      if (0.0 <= x && x < r.get_width() && 0.0 <= y && y < r.get_height())
        r[x, y] = color;
    });
  }
};

namespace {
  template <class Sf>
  struct FromStaticFigureImpl;

  template <class... Fs>
  struct FromStaticFigureImpl<figure::StaticFigure<Fs...>> {
    using t = Shape<Fs...>;
  };
} // namespace

template <class Sf>
using FromStaticFigure = FromStaticFigureImpl<Sf>::t;
} // namespace shape

#endif
