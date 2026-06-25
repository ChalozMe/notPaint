#pragma once

#include "Object.h"

class PolylineObject : public Object {

public:

    PolylineObject();

    void addPoint(Vec2 p);

    void draw() override;

    bool contains(Vec2 p) override;

    ObjectType getType() override;
};
