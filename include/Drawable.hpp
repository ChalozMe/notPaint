#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "PixelGrid.hpp"

struct Drawable {
  PixelCoord position;
  Vector2 scale;
  Radians rotation; // in radians
  Color color;

  Drawable(PixelCoord p, Vector2 s, Radians r, Color c) :
    position{p},
    scale{s},
    rotation{r},
    color{c} {}

  virtual ~Drawable() = default;
  virtual void render(PixelGrid&) const = 0;
};

#endif
