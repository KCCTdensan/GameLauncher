#include "SceneManager.h"

SceneBase* SceneManager::currentScene = nullptr;
std::map<std::string, SceneBase*> SceneManager::scenes;
std::array<SceneSet, ApplicationPreference::sceneHistories> SceneManager::sceneHistory{ SceneSet("_blank", new BlankRedirectScene()) ,SceneSet("_blank", new BlankRedirectScene()) ,SceneSet("_blank", new BlankRedirectScene()) ,SceneSet("_blank", new BlankRedirectScene()) };
int SceneManager::sceneHistoryPosition = 0;

bool SceneManager::AddScene(std::string sceneName, SceneBase* scene)
{
	scenes.insert(std::make_pair(sceneName, scene));
	return true;
}

bool SceneManager::CheckScene(std::string sceneName)
{
	if (scenes.count(sceneName) >= 1)
		return true;
	return false;
}

bool SceneManager::ChangeScene(std::string sceneName, SceneBase* altScene, bool addSceneToMap)
{
	bool changed = false;
	if (scenes.count(sceneName) >= 1) {
		currentScene = scenes[sceneName];
		changed = true;
	}
	else {
		if (addSceneToMap) {
			AddScene(sceneName, altScene);
			ChangeScene(sceneName, altScene);
		}
		else {
			currentScene = altScene;
			changed = true;
		}
	}
	if (changed) {
		Update();
		std::rotate(sceneHistory.begin(), sceneHistory.begin() + ApplicationPreference::sceneHistories - 1, sceneHistory.end());
		sceneHistory[0] = SceneSet(sceneName, currentScene);
	}
	return true;
}

bool SceneManager::ChangeSceneBackward()
{
	sceneHistoryPosition++;
	if (sceneHistoryPosition >= ApplicationPreference::sceneHistories)
		sceneHistoryPosition = ApplicationPreference::sceneHistories - 1;
	currentScene = sceneHistory[sceneHistoryPosition].scene;
	return true;
}

bool SceneManager::ChangeSceneForward()
{
	sceneHistoryPosition--;
	if (sceneHistoryPosition < 0)
		sceneHistoryPosition = 0;
	currentScene = sceneHistory[sceneHistoryPosition].scene;
	return true;
}

void SceneManager::Update() {
	currentScene->Update();
}

void SceneManager::Draw() {
	currentScene->Draw();
}