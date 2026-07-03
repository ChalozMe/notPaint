#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "../math/Vec2.hpp"
#include "../math/Color.hpp"

class Object {
protected:
  std::vector<Vec2> vertices;

  Color borderColor;

  Color fillColor;

  bool selected = false;
  bool filled = false;

  float tx = 0.0f;
  float ty = 0.0f;

  float angle = 0.0f;

  float sx = 1.0f;
  float sy = 1.0f;

public:
  virtual ~Object() = default;
  virtual void draw() = 0;
  virtual bool contains(Vec2 p) = 0;

  void setSelected(bool value) {
    selected = value;
  }

  bool isSelected() {
    return selected;
  }

  void translate(float dx, float dy) {
    tx += dx;
    ty += dy;
  }

  void rotate(float da) {
    angle += da;
  }

  void scale(float dsx, float dsy) {
    sx *= dsx;
    sy *= dsy;
  }

  void setBorderColor(Color color) {
    borderColor = color;
  }

  Color getBorderColor() const {
    return borderColor;
  }

  void setFillColor(Color color) {
    fillColor = color;
  }

  void setFilled(bool value) {
    filled = value;
  }
};

#endif
