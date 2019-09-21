#pragma once
#include "SceneData.h"
#include "DxLib.h"

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

	static int ChanegeScene(SCENE scene);
	static void Update();
	static void Draw();

	bool quitFlag = FALSE;

private:

	static SceneData* currentScene;
};

