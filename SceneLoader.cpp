#include "SceneLoader.h"
#include "Scene.h"

void SceneLoader::addScene(std::string const& name, Scene* const newScene)
{
	//get index of this scene
	int index = (int)scenes.size();

	//add scene to list
	scenes.push_back(newScene);

	//add to name indexes with index
	sceneNameIndexes[name] = index;
}
