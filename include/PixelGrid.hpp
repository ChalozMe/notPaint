#ifndef PIXEL_GRID_HPP
#define PIXEL_GRID_HPP

#include <algorithm>
#include <cstddef>
#include <vector>

struct Vector2 {
  float x;
  float y;
};

struct PixelCoord {
  std::size_t x;
  std::size_t y;
};

using Radians = float;

struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

static constexpr Color BLACK = Color{0, 0, 0, 255};
static constexpr Color WHITE = Color{255, 255, 255, 255};

class PixelGrid {
  std::size_t w;
  std::size_t h;
  std::vector<Color> grid;

public:
  PixelGrid(std::size_t _w, std::size_t _h) :
    w(_w),
    h(_h),
    grid(w * h, WHITE) {}

  const Color* data() const {
    return grid.data();
  }

  Color* data() {
    return grid.data();
  }

  const Color& operator[](std::size_t x, std::size_t y) const {
    return grid[y * w + x];
  }

  Color& operator[](std::size_t x, std::size_t y) {
    return grid[y * w + x];
  }

  std::size_t width() const {
    return w;
  }

  std::size_t height() const {
    return h;
  }

  void clear(Color color = WHITE) {
    std::ranges::fill(grid, color);
  }
};

#endif
