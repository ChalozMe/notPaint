#pragma once

#include "Object.h"

class PointObject : public Object {

public:

    PointObject(Vec2 p);

    void draw() override;

    bool contains(Vec2 p) override;

    ObjectType getType() override;
};
