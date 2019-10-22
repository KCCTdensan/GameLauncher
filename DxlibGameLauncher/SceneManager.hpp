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


class SceneManager
{
public:
	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;
	SceneManager(SCENE firstScene, ObjectManager &objectManager);
	~SceneManager();

	int ChanegeScene(SCENE scene);
	void Update();
	void Draw();
	
private:
	SceneData *currentScene;
	std::array<SceneData *, SCENE_NUM> sceneSave;
};