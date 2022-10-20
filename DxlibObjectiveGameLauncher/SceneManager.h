#pragma once
#include <map>
#include <array>
#include <string>
#include <algorithm>
#include "SceneBase.h"
#include "SceneSet.h"
#include "ApplicationPreference.h"
#include "BlankRedirectScene.h"
#include "ObjectOverlapping.h"
#include "SharingScenes.h"

class Header;
class PopupScene;

class SceneManager {
public:

	static bool AddScene(std::string sceneName, SceneBase* scene);
	static bool CheckScene(std::string sceneName);
	static bool ChangeScene(std::string sceneName, SceneBase* altScene, bool addSceneToMap = true, bool deleteNotAddedScene = true);
	static bool ChangeSceneBackward();
	static bool ChangeSceneForward();
	static int GetSceneHistoryPosition() { return sceneHistoryPosition; }
	static bool UpdateForwardBackwardScene(int forwardButton, int forwardFrame, int backwardButton, int backwardFrame);

	static SharingScenes* GetSharingScenes() {
		return &sharingScenes;
	}

	static void Initialize();

	static void Collide();
	static void Update();
	static void Draw();

private:
	static bool beInitialized;
	static bool isAddingMap;
	static bool deleteNotAddedScene;
	static SceneSet current;
	static std::map<std::string, SceneBase*> scenes;
	static std::array<SceneSet, ApplicationPreference::sceneHistories> sceneHistory;
	static int sceneHistoryPosition;
	static SceneSet blankScene;
	static Header* header;
	static PopupScene* popupScene;
	static SharingScenes sharingScenes;
};