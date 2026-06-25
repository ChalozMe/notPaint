#include "Renderer.h"

#include <GL/glut.h>

#include "Globals.h"

void initRenderer()
{
    glClearColor(1,1,1,1);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    scene.draw();

    glutSwapBuffers();
}
