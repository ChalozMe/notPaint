#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/freeglut_std.h>
#include <concepts>

template <class S>
concept Scene = std::invocable<decltype(&S::display), const S&> &&
  std::invocable<decltype(&S::idle), S&>;

template <class S>
concept KeyboardInput =
  std::invocable<decltype(&S::keyboard), S&, unsigned char, int, int> &&
  std::invocable<decltype(&S::special), S&, int, int, int>;

template <class S>
concept MouseInput =
  std::invocable<decltype(&S::mouse), S&, int, int, int, int> &&
  std::invocable<decltype(&S::motion), S&, int, int>;

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

template <Scene S>
void play_scene(int argc, char* argv[], const char* title) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(title);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.f, 0.f, 0.f, 1.f);

  static S scene;

  glutDisplayFunc([]() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene.display();
    glutSwapBuffers();
  });

  glutIdleFunc([]() {
    scene.idle();
    glutPostRedisplay();
  });

  if constexpr (KeyboardInput<S>) {
    glutKeyboardFunc([](unsigned char key, int x, int y) {
      scene.keyboard(key, x, y);
    });

    glutSpecialFunc([](int key, int x, int y) { scene.special(key, x, y); });
  }

  if constexpr (MouseInput<S>) {
    glutMouseFunc([](int button, int state, int x, int y) {
      scene.mouse(button, state, x, y);
    });

    glutMotionFunc([](int x, int y) { scene.motion(x, y); });
  }

  glutReshapeFunc([](int width, int height) {
    if (height == 0)
      height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  });

  glutMainLoop();
}

#endif
