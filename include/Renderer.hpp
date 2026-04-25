#pragma once
#include <vector>

#include "Pixel.hpp"

// OpenGL Legacy
class Renderer {
  uint32_t textureId;

  struct Sprite {
    unsigned width;
    unsigned height;
    std::vector<Pixel> buffer;

    inline void setPixel(unsigned x, unsigned y, Pixel p) {
      if (x < width && y < height) {
        buffer[y * width + x] = p;
      }
    }

    inline Pixel getPixel(unsigned x, unsigned y) const {
      if (x < width && y < height) {
        return buffer[y * width * x];
      } else {
        return Pixel{};
      } 
    }
  } sprite;

  Renderer(uint32_t textureId, Sprite&& sprite) :
    textureId{textureId},
    sprite{std::move(sprite)} {}

public:
  static Renderer create(unsigned width, unsigned height);

  Renderer(Renderer&& o);
  Renderer& operator=(Renderer&& o);
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  ~Renderer();

  void clear(Pixel p);
  void drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, Pixel p);
  void draw(unsigned x, unsigned y, Pixel p);

  void send2Gpu() const;
};
