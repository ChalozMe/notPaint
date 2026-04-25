#include "Renderer.hpp"

#include <GL/gl.h>
#include <algorithm>
#include <utility>

Renderer Renderer::create(unsigned width, unsigned height) {
  uint32_t id = 0;

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_CULL_FACE);

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

  return Renderer(
    id,
    Sprite{.width = width, .height = height, .buffer = {width * height, Pixel{}}}
  );
}


Renderer::Renderer(Renderer&& o) : 
  textureId{std::exchange(o.textureId, 0)},
  sprite{std::move(o.sprite)} {}

Renderer& Renderer::operator=(Renderer&& o) {
  textureId = std::exchange(o.textureId, 0);
  sprite = std::move(o.sprite);

  return *this;
}

Renderer::~Renderer() {
  glDeleteTextures(1, &textureId);
}

void Renderer::send2Gpu() const {
  // Prepare Texture
  {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexSubImage2D(
      GL_TEXTURE_2D,
      0,
      0,
      0,
      sprite.width,
      sprite.height,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      sprite.buffer.data()
    );
  }

  // Draw Texture
  {
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
}

// ==================
// DRAWING FUNCTIONS
// ===================
void Renderer::draw(unsigned x, unsigned y, Pixel p) {
  if(x < sprite.width && y < sprite.height) {
    sprite.setPixel(x, y, p);
  }
}

void Renderer::clear(Pixel p) {
  std::ranges::fill(sprite.buffer, p);
}

void Renderer::drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, Pixel p) {
  for(auto x = x0; x <= x1; ++x) {
    for(auto y = y0; y <= y1; ++y) {
      draw(x, y, p);
    }
  }
}  
