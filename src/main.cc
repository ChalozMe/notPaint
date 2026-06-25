#include <GL/glut.h>

#include "core/Input.h"

#include "core/Renderer.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB
    );

    glutInitWindowSize(800,600);

    glutCreateWindow("Editor");

    initRenderer();

    glutDisplayFunc(renderScene);

    glutMouseFunc(mouseCallback);

    glutKeyboardFunc(keyboardCallback);

    glutReshapeFunc(reshapeCallback);

    glutMainLoop();

    return 0;
}
