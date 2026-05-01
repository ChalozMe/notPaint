#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/gl.h>
#include <utility>
#include <vector>

#include "Color.hpp"

// OpenGL Legacy
class Renderer {
  std::size_t width;
  std::size_t height;
  std::vector<Color> buffer;
  uint32_t texture_id;

  static uint32_t make_texture(std::size_t width, std::size_t height) {
    // This affects global state, we probably should do this somewhere else outside of this class
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);

    uint32_t id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      width,
      height,
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      nullptr
    );
    return id;
  }

public:
  //getter, change cos it ez solution, 
  std::size_t get_width() const { return width; }
  std::size_t get_height() const { return height; }

  Renderer(std::size_t w, std::size_t h) :
    width{w},
    height{h},
    buffer(w * h, Colors::BLACK),
    texture_id{make_texture(w, h)} {}

  Renderer(Renderer&& o) :
    width{std::exchange(o.width, 0)},
    height{std::exchange(o.height, 0)},
    buffer{std::exchange(o.buffer, std::vector<Color>())},
    texture_id{std::exchange(o.texture_id, 0)} {}

  Renderer& operator=(Renderer&& o) {
    if (this != &o) {
      this->~Renderer();
      new (this) Renderer(std::move(o));
    }
    return *this;
  }

  ~Renderer() {
    glDeleteTextures(1, &texture_id);
  }

  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;

  void clear(Color p) {
    std::ranges::fill(buffer, p);
  }

  Color operator[](std::size_t x, std::size_t y) const {
    return buffer[y * width + x];
  }

  Color& operator[](std::size_t x, std::size_t y) {
    return buffer[y * width + x];
  }

  void send_to_gpu() const {
    // Prepare Texture
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexSubImage2D(
      GL_TEXTURE_2D,
      0,
      0,
      0,
      width,
      height,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      buffer.data()
    );

    // Draw Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(-1.f, 1.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.f, 1.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.f, -1.f);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(-1.f, -1.f);
    glEnd();
  }
};

#endif
