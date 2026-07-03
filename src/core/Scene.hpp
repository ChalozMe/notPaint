#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "../objects/Object.hpp"

class Scene {
  std::vector<Object*> objects;
  Object* selectedObject = nullptr;

public:
  void add(Object* obj) {
    objects.push_back(obj);
  }

  void draw() {
    for (auto obj : objects)
      obj->draw();
  }

  Object* select(Vec2 p) {
    if (selectedObject)
      selectedObject->setSelected(false);

    selectedObject = nullptr;

    for (auto obj : objects) {
      if (obj->contains(p)) {
        obj->setSelected(true);

        selectedObject = obj;

        return obj;
      }
    }

    return nullptr;
  }

  Object* getSelected() {
    return selectedObject;
  }
};

#endif
