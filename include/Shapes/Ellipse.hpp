#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Drawable.hpp"

class Ellipse: public Drawable {
public:
  Ellipse(PixelCoord center, Vector2 axis, Color color) :
    Drawable(center, axis, 0.0f, color) {}

  virtual ~Ellipse() override = default;

  virtual void render(PixelGrid& grid) const override {
    float cx = static_cast<float>(position.x);
    float cy = static_cast<float>(position.y);

    float a = scale.x;
    float b = scale.y;

    if (a <= 0.0f || b <= 0.0f)
      return;

    std::size_t min_x = static_cast<std::size_t>(std::max(0.0f, cx - a));
    std::size_t max_x =
      static_cast<std::size_t>(std::min<float>(grid.width() - 1, cx + a));
    std::size_t min_y = static_cast<std::size_t>(std::max(0.0f, cy - b));
    std::size_t max_y =
      static_cast<std::size_t>(std::min<float>(grid.height() - 1, cy + b));

    float a2 = a * a;
    float b2 = b * b;

    for (std::size_t y = min_y; y <= max_y; ++y) {
      for (std::size_t x = min_x; x <= max_x; ++x) {
        float dx = (static_cast<float>(x) + 0.5f) - cx;
        float dy = (static_cast<float>(y) + 0.5f) - cy;

        float v = (dx * dx) / a2 + (dy * dy) / b2;

        if (v <= 1.0f) {
          grid[x, y] = color;
        }
      }
    }
  }
};

#endif
