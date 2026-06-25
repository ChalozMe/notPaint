#pragma once

#include "Object.h"

class PolygonObject : public Object {

public:

    PolygonObject();

    void addPoint(Vec2 p);

    void setFilled(bool value);

    void draw() override;

    bool contains(Vec2 p) override;

    ObjectType getType() override;
};
