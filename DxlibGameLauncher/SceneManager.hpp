#pragma once
#include "SceneList.h"

#include "TAB_APP_Scene.hpp"
#include "TAB_GAME_Scene.hpp"
#include "TAB_HOME_Scene.hpp"
#include "TAB_MUSIC_Scene.hpp"
#include "TAB_3DMODEL_Scene.hpp"
#include "TAB_VIDEO_Scene.hpp"
#include "TAB_OTHERS_Scene.hpp"


class SceneManager
{
public:
	SceneManager(ObjectManager &objectManager);
	~SceneManager();

	int ChanegeScene(SCENE scene);
	void Update();
	void Draw();

	//bool quitFlag;

private:
	ObjectManager &objectManager;
	SceneData *currentScene;
	
	SceneData* sceneSave[SCENE_NUM];
};