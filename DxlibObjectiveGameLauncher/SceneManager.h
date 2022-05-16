#pragma once
#include <map>
#include <array>
#include <string>
#include <algorithm>
#include "SceneBase.h"
#include "SceneSet.h"
#include "DebugScene.h"
#include "ApplicationPreference.h"
#include "BlankRedirectScene.h"

class SceneManager {
public:

	static bool AddScene(std::string sceneName, SceneBase* scene);
	static bool CheckScene(std::string sceneName);
	static bool ChangeScene(std::string sceneName, SceneBase* altScene, bool addSceneToMap = true);
	static bool ChangeSceneBackward();
	static bool ChangeSceneForward();
	static void Update();
	static void Draw();

protected:
	static SceneBase* currentScene;
	static std::map<std::string, SceneBase*> scenes;
	static std::array<SceneSet, ApplicationPreference::sceneHistories> sceneHistory;
	static int sceneHistoryPosition;
};