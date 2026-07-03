#ifndef POLYGON_OBJECT_HPP
#define POLYGON_OBJECT_HPP

#include "Object.hpp"
#include <GL/glut.h>
#include "../utils/Selection.hpp"

struct PolygonObject: Object {
  PolygonObject() = default;
  virtual ~PolygonObject() override = default;

  void addPoint(Vec2 p) {
    vertices.push_back(p);
  }

  void setFilled(bool value) {
    filled = value;
  }

  virtual void draw() override {
    glPushMatrix();
    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);

    if (filled) {
      glColor3f(fillColor.r, fillColor.g, fillColor.b);
      glBegin(GL_POLYGON);
      for (auto& v : vertices)
        glVertex2f(v.x, v.y);
      glEnd();
    }

    glLineWidth(selected ? 4 : 2);

    glColor3f(borderColor.r, borderColor.g, borderColor.b);
    glBegin(GL_LINE_LOOP);
    for (auto& v : vertices)
      glVertex2f(v.x, v.y);
    glEnd();
    glPopMatrix();
  }

  virtual bool contains(Vec2 p) override {
    if (vertices.size() < 3)
      return false;

    for (size_t i = 0; i < vertices.size(); i++) {
      Vec2 a = vertices[i];
      Vec2 b = vertices[(i + 1) % vertices.size()];
      if (pointSegmentDistance(p, a, b) < 8.0f) {
        return true;
      }
    }
    return false;
  }
};

#endif
