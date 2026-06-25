#pragma once

#include <vector>
#include "../objects/Object.h"

class Scene 
{
private:
    std::vector<Object*> objects;
    Object* selectedObject = nullptr;
public:
    void add(Object* obj);
    void draw();
    Object* select(Vec2 p);
    Object* getSelected();
};
