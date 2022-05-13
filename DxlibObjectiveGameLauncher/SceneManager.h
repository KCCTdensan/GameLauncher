#pragma once
#include <vector>
#include "SceneBase.h"
#include "DebugScene.h"

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void Update();
	void Draw();

protected:
	SceneBase* currentScene;
};