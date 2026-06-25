#include "LineObject.h"
#include "../utils/Selection.h"

#include <GL/glut.h>

#include <cmath>

LineObject::LineObject(Vec2 a, Vec2 b)
{
    vertices.push_back(a);
    vertices.push_back(b);
}

void LineObject::draw()
{
    glPushMatrix();
    //
    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);
    //
    glLineWidth(selected ? 4 : 2);

    glBegin(GL_LINES);
        glColor3f(borderColor.r, borderColor.g, borderColor.b);
        glVertex2f(vertices[0].x, vertices[0].y);
        glVertex2f(vertices[1].x, vertices[1].y);
    glEnd();
    glPopMatrix();
}


ObjectType LineObject::getType()
{
    return ObjectType::LINE;
}

bool LineObject::contains(Vec2 p)
{
    return pointSegmentDistance(
        p,
        vertices[0],
        vertices[1]
    ) < 8.0f;
}
