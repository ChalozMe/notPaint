#ifndef LINE_OBJECT_HPP
#define LINE_OBJECT_HPP

#include "Object.hpp"
#include <GL/glut.h>
#include "../utils/Selection.hpp"

struct LineObject: Object {
  LineObject(Vec2 a, Vec2 b) {
    vertices.push_back(a);
    vertices.push_back(b);
  }

  virtual void draw() override {
    glPushMatrix();

    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);

    glLineWidth(selected ? 4 : 2);
    glBegin(GL_LINES);
    glColor3f(borderColor.r, borderColor.g, borderColor.b);
    glVertex2f(vertices[0].x, vertices[0].y);
    glVertex2f(vertices[1].x, vertices[1].y);
    glEnd();

    glPopMatrix();
  }

  virtual bool contains(Vec2 p) override {
    return pointSegmentDistance(p, vertices[0], vertices[1]) < 8.0f;
  }
};

#endif
