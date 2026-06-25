#pragma once
#include "Object.h"


class LineObject : public Object {

public:

    LineObject(Vec2 a, Vec2 b);

    void draw() override;

    bool contains(Vec2 p) override;

    ObjectType getType() override;
};
