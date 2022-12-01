#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Object.h"

class GameObject;

class Scene :
    public Object
{
protected:
    std::vector<GameObject*> gameObjectsInScene;

public:
    Scene();
    ~Scene();
};

#endif
