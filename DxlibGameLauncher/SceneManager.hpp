#pragma once


#include "SceneList.h"

#include "TAB_APP_Scene.hpp"
#include "TAB_GAME_Scene.hpp"
#include "TAB_HOME_Scene.hpp"
#include "TAB_MUSIC_Scene.hpp"
#include "TAB_3DMODEL_Scene.hpp"
#include "TAB_VIDEO_Scene.hpp"
#include "TAB_OTHERS_Scene.hpp"
#include <array>
#include "JsonManager.h"


class SceneManager
{
public:
	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;
	SceneManager(ObjectManager &objectManager, Json& json, JsonManager& jsonManager);
	~SceneManager();

	int ChanegeScene(SCENE scene);
	void Update();
	void Draw();
	
private:
	SceneData *currentScene;
	std::array<SceneData *, (int)SCENE::SCENE_NUM> sceneSave;
};