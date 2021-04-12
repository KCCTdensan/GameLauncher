#pragma once


#include "SceneList.h"

#include "SceneProc.h"
#include "SceneProcHome.h"
#include <array>
#include "JsonManager.h"


class SceneManager
{
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(ObjectManager& objectManager, Json& json, JsonManager& jsonManager);
	~SceneManager();

	int ChanegeScene(SCENE scene);
	void Update();
	void Draw();

private:
	SceneProc* currentScene;
	std::array<SceneProc*, (int)SCENE::SCENE_NUM> sceneSave;
};