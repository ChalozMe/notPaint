#ifndef POINT_OBJECT_HPP
#define POINT_OBJECT_HPP

#include "Object.hpp"
#include <GL/glut.h>
#include <cmath>

struct PointObject: Object {
  PointObject(Vec2 p) {
    vertices.push_back(p);
  }

  virtual void draw() override {
    glPushMatrix();
    //multipl.
    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);
    //
    glPointSize(selected ? 8 : 5);
    glBegin(GL_POINTS);
    glColor3f(borderColor.r, borderColor.g, borderColor.b);
    glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();
    glPopMatrix();
  }

  virtual bool contains(Vec2 p) override {
    float dx = p.x - vertices[0].x;
    float dy = p.y - vertices[0].y;

    float d = std::hypot(dx, dy);

    return d < 8.0f;
  }
};

#endif
