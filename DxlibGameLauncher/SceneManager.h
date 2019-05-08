#pragma once

#include <DxLib.h>
#include "SceneData.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	enum SCENE
	{
		MAIN
	};

	static int ChanegeScene(SCENE scene);
	static void Update();
	static void Draw();

	bool quitFlag = FALSE;

private:

	static SceneData* currentScene;
};