#include "PointObject.h"
#include <cmath>
#include <GL/glut.h>

PointObject::PointObject(Vec2 p) 
{
  vertices.push_back(p);
}


void PointObject::draw() 
{
    glPushMatrix();
    //multipl.
    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);
    //
    glPointSize(selected ? 8 : 5);
    glBegin(GL_POINTS);
      glColor3f(borderColor.r ,borderColor.g, borderColor.b);
      glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();
    glPopMatrix();
}


bool PointObject::contains(Vec2 p)
{
    float dx = p.x - vertices[0].x;
    float dy = p.y - vertices[0].y;

    float d =  sqrt(dx*dx + dy*dy);

    return d < 8.0f;
}

ObjectType PointObject::getType()
{
    return ObjectType::POINT;
}
