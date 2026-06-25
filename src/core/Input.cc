#include "Input.h"

#include <GL/glut.h>

#include "../core/Globals.h"

#include "../objects/PointObject.h"
#include "../objects/LineObject.h"
#include "../objects/PolylineObject.h"
#include "../objects/PolygonObject.h"

PolylineObject* currentPolyline = nullptr;

PolygonObject* currentPolygon = nullptr;

bool waitingSecondPoint = false;

//Object* selected = scene.getSelected();

Vec2 firstPoint;


void reshapeCallback(int width, int height)
{
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(0, width,0, height);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    Object* selected = scene.getSelected();
    switch(key)
    {
        case '1':
            currentMode = Mode::DRAW_POINT;
            break;

        case '2':
            currentMode = Mode::DRAW_LINE;
            break;

        case '3':
            currentMode = Mode::DRAW_POLYLINE;
            break;

        case '4':
            currentMode = Mode::DRAW_POLYGON;
            break;

        case 'c':

            if(currentPolygon)
            {
                scene.add(currentPolygon);
                currentPolygon = nullptr;
            }

            if(currentPolyline)
            {
                scene.add(currentPolyline);
                currentPolyline = nullptr;
            }
            break;

        case 'f':
          if(selected)
          selected->setFilled(true);
          break;

        case 'u':
          if(selected)
          selected->setFilled(false);
          break;

        case '0':
            currentMode = Mode::SELECT;
            break;

        case 'w':
          if(selected)
          selected->translate(0,10);
          break;

        case 's':
          if(selected)
          selected->translate(0,-10);
          break;

        case 'a':
          if(selected)
          selected->translate(-10,0);
          break;

        case 'd':
          if(selected)
          selected->translate(10,0);
          break;

        case 'q':
          if(selected)
          selected->rotate(5);
          break;

        case 'e':
          if(selected)
          selected->rotate(-5);
          break;

        case '+':
          if(selected)
          selected->scale(1.1f,1.1f);
        break;

        case '-':
          if(selected)
          selected->scale(0.9f,0.9f);
          break;

        case 'r':
          if(selected)
          selected->setBorderColor({1,0,0});
          break;

        case 'g':
          if(selected)
          selected->setBorderColor({0,1,0});
          break;

        case 'b':
          if(selected)
          selected->setBorderColor({0,0,1});
          break;

        case 'y':
          if(selected)
          selected->setBorderColor({1,1,0});
          break;

        case 'p':
          if(selected)
          selected->setBorderColor({0.5,0,0.5});
          break;

        case 'R':
          if(selected)
          selected->setFillColor({1,0,0});
          break;

        case 'G':
          if(selected)
          selected->setFillColor({0,1,0});
          break;

        case 'B':
          if(selected)
          selected->setFillColor({0,0,1});
          break;

        case 'Y':
          if(selected)
          selected->setFillColor({1,1,0});
          break;

        case 'P':
          if(selected)
          selected->setFillColor({0.5,0,0.5});
          break;

    }
    glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y)
{
    if(button != GLUT_LEFT_BUTTON || state  != GLUT_DOWN)
        return;

    float fx = x;
    float fy = windowHeight - y;
    Vec2 p = {fx, fy};

    switch(currentMode)
    {
        case Mode::DRAW_POINT:
            scene.add(
                new PointObject(p)
            );
            break;

        case Mode::DRAW_LINE:
            if(!waitingSecondPoint)
            {
                firstPoint = p;
                waitingSecondPoint = true;
            }
            else
            {
                scene.add(new LineObject(firstPoint, p));
                waitingSecondPoint = false;
            }
            break;

        case Mode::DRAW_POLYLINE:
            if(!currentPolyline)
                currentPolyline = new PolylineObject();
            currentPolyline->addPoint(p);
            break;

        case Mode::DRAW_POLYGON:
            if(!currentPolygon)
                currentPolygon = new PolygonObject();
            currentPolygon->addPoint(p);
            break;

        case Mode::SELECT:
          scene.select(p);
          break;

        default:
            break;
    }

    glutPostRedisplay();
}
