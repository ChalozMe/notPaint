#ifndef POLYLINE_OBJECT_HPP
#define POLYLINE_OBJECT_HPP

#include "Object.hpp"
#include <GL/glut.h>
#include "../utils/Selection.hpp"

struct PolylineObject: Object {
  PolylineObject() = default;
  virtual ~PolylineObject() override = default;

  void addPoint(Vec2 p) {
    vertices.push_back(p);
  }

  virtual void draw() override {
    glPushMatrix();

    glTranslatef(tx, ty, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(sx, sy, 1);
    glLineWidth(selected ? 4 : 2);

    glBegin(GL_LINE_STRIP);
    glColor3f(borderColor.r, borderColor.g, borderColor.b);
    for (auto& v : vertices)
      glVertex2f(v.x, v.y);
    glEnd();

    glPopMatrix();
  }

  virtual bool contains(Vec2 p) override {
    if (vertices.size() < 2)
      return false;

    for (size_t i = 0; i < vertices.size() - 1; i++) {
      if (pointSegmentDistance(p, vertices[i], vertices[i + 1]) < 8.0f) {
        return true;
      }
    }
    return false;
  }
};

#endif
