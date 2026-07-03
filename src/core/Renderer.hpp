#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Globals.hpp"
#include <GL/glut.h>

inline void initRenderer() {
  glClearColor(1, 1, 1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

inline void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  scene.draw();
  glutSwapBuffers();
}

#endif
