#pragma once
#include "SceneBase.h"
#include <string>

struct SceneSet {
	std::string sceneName;
	SceneBase* scene;
	bool addSceneToMap;
	bool deleteNotAddedScene;

	SceneSet(std::string _sceneName, SceneBase* _scene, bool _addSceneToMap = true, bool _deleteNotAddedScene = true)
		: sceneName(_sceneName), scene(_scene), addSceneToMap(_addSceneToMap), deleteNotAddedScene(_deleteNotAddedScene) {}
	SceneSet() : sceneName(""), scene(nullptr), addSceneToMap(true), deleteNotAddedScene(true) {}
};