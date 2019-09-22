#pragma once

#include "TAB_APP_Scene.hpp"
#include "TAB_GAME_Scene.hpp"
#include "TAB_HOME_Scene.hpp"
#include "TAB_MUSIC_Scene.hpp"


constexpr int SCENE_NUM = 1;

enum SCENE
{
	TAB_HOME,
	TAB_APP,
	TAB_GAME,
	TAB_MUSIC
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	int ChanegeScene(SCENE scene);
	void Update();
	void Draw();

	//bool quitFlag;

private:
	SceneData *currentScene;
};