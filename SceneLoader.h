#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <map>
#include <vector>
#include "Object.h"

class Scene;

class SceneLoader :
    public Object
{
private:
    std::vector<Scene*> scenes;
    std::map<std::string, int> sceneNameIndexes;

public:
    SceneLoader();
    ~SceneLoader();

    void addScene(std::string const& name, Scene* const newScene);
};

#endif
