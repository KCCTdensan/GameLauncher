#include "SceneManager.h"

SceneBase* SceneManager::currentScene = nullptr;
std::map<std::string, SceneBase*> SceneManager::scenes;

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
	if (scenes.count(sceneName) >= 1)
		currentScene = scenes[sceneName];
	else {
		if (addSceneToMap) {
			AddScene(sceneName, altScene);
			ChangeScene(sceneName, altScene);
		}
		else {
			currentScene = altScene;
		}
	}
	return true;
}

void SceneManager::Update() {
	currentScene->Update();
}

void SceneManager::Draw() {
	currentScene->Draw();
}