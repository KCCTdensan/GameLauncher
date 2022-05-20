#pragma once
#include "SceneBase.h"
#include <string>

struct SceneSet {
	std::string sceneName;
	SceneBase* scene;

	SceneSet(std::string _sceneName, SceneBase* _scene) : sceneName(_sceneName), scene(_scene) {}
	SceneSet() : sceneName(""), scene(nullptr) {}
};