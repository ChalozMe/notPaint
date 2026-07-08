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
  float tx = 0.0f;
  float ty = 0.0f;
  float sx = 1.0f;
  float sy = 1.0f;
  float angle = 0.0f;

  bool is_clicked(std::size_t click_x, std::size_t click_y) const {
    auto [min_x, min_y, max_x, max_y] = bounding_box();
    auto cx = std::midpoint(min_x, max_x);
    auto cy = std::midpoint(min_y, max_y);

    bool is_clicked = false;
    figure.visit_pixels([&](std::size_t px, std::size_t py) {
      auto [fx, fy] = transform(px, py, cx, cy);
      if (0 <= fx && 0 <= fy) {
        std::size_t x = fx;
        std::size_t y = fy;
        is_clicked = is_clicked || (x == click_x && y == click_y);
      }
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

  std::pair<float, float>
  transform(float x, float y, float cx, float cy) const {
    float dx = sx * (x - cx);
    float dy = sy * (y - cy);
    float rx = dx * std::cos(angle) - dy * std::sin(angle);
    float ry = dx * std::sin(angle) + dy * std::cos(angle);

    return {rx + tx + cx, ry + ty + cy};
  }

  void draw(Renderer& r) const {
    auto [min_x, min_y, max_x, max_y] = bounding_box();
    auto cx = std::midpoint(min_x, max_x);
    auto cy = std::midpoint(min_y, max_y);

    figure.visit_pixels([&](std::size_t px, std::size_t py) {
      auto [x, y] = transform(px, py, cx, cy);
      if (0.0f <= x && x < r.get_width() && 0.0f <= y && y < r.get_height())
        r[static_cast<std::size_t>(x), static_cast<std::size_t>(y)] = color;
    });
  }
};
} // namespace shape

#endif
