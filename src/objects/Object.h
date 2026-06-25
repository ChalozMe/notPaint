#pragma once

#include <vector>

#include "../math/Vec2.h"
#include "../math/Color.h"

#include "../enums/ObjectType.h"

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

    virtual void draw() = 0;

    virtual bool contains(Vec2 p) = 0;

    virtual ObjectType getType() = 0;

    void setSelected(bool value);

    bool isSelected();

    void translate(float dx, float dy);

    void rotate(float da);

    void scale(float dsx, float dsy);

    virtual ~Object();

    void setBorderColor(Color color);
 
    Color getBorderColor() const;
    
    void setFillColor(Color color);

    void setFilled(bool value);
};
