#include "Object.h"

void Object::setSelected(bool value)
{
  selected = value;
}

bool Object::isSelected()
{
  return selected;
}

void Object::translate(float dx, float dy)
{
  tx += dx;
  ty += dy;
}

void Object::rotate(float da)
{
  angle += da;
}

void Object::scale(float dsx, float dsy)
{
  sx *= dsx;
  sy *= dsy;
}

void Object::setBorderColor(Color color)
{
    borderColor = color;
}

Color Object::getBorderColor() const
{
    return borderColor;
}

void Object::setFillColor(Color color)
{
    fillColor = color;
}

void Object::setFilled(bool value)
{
    filled = value;
}

Object::~Object() {}
