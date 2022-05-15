#pragma once
#include <map>
#include <string>
#include "SceneBase.h"

class SceneManager {
public:

	static bool AddScene(std::string sceneName, SceneBase* scene);
	static bool CheckScene(std::string sceneName);
	static bool ChangeScene(std::string sceneName, SceneBase* altScene, bool addSceneToMap = true);
	static void Update();
	static void Draw();

protected:
	static SceneBase* currentScene;
	static std::map<std::string, SceneBase*> scenes;
};