#pragma once

#include "TAB_APP_Scene.hpp"
#include "TAB_GAME_Scene.hpp"
#include "TAB_HOME_Scene.hpp"
#include "TAB_MUSIC_Scene.hpp"


enum SCENE
{
	TAB_HOME,
	TAB_APP,
	TAB_GAME,
	TAB_MUSIC,
	SCENE_NUM
};

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
};