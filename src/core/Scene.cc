#include "Scene.h"

void Scene::add(Object* obj)
{
    objects.push_back(obj);
}

void Scene::draw()
{
    for(auto obj : objects)
        obj->draw();
}

Object* Scene::select(Vec2 p)
{
    if(selectedObject)
        selectedObject->setSelected(false);

    selectedObject = nullptr;

    for(auto obj : objects)
    {
        if(obj->contains(p))
        {
            obj->setSelected(true);

            selectedObject = obj;

            return obj;
        }
    }

    return nullptr;
}

Object* Scene::getSelected()
{
    return selectedObject;
}
