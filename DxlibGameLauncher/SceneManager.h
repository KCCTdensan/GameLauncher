#pragma once
#include "SceneData.h"
#include "DxLib.h"

constexpr int SCENE_NUM = 1;

enum SCENE
{
	MAIN
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

