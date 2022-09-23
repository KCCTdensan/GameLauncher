#include "SceneManager.h"
#include "Header.h"
#include "PopupScene.h"

std::map<std::string, SceneBase*> SceneManager::scenes;
std::array<SceneSet, ApplicationPreference::sceneHistories> SceneManager::sceneHistory{};
int SceneManager::sceneHistoryPosition = 0;
bool SceneManager::beInitialized = false;
SceneSet SceneManager::blankScene = SceneSet("_blank", new BlankRedirectScene());
SceneSet SceneManager::current = SceneSet("", nullptr);
Header* SceneManager::header = nullptr;
PopupScene* SceneManager::popupScene = nullptr;
SharingScenes SceneManager::sharingScenes;

void SceneManager::Initialize()
{
	if (beInitialized) return;
	
	header = new Header();
	popupScene = new PopupScene();
	sharingScenes.header = header;
	sharingScenes.popupScene = popupScene;

	//header->Initialize();
	sceneHistory.fill(blankScene);

	beInitialized = true;
}

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
		current = SceneSet(sceneName, scenes[sceneName]);
		changed = true;
		//delete (altScene); (altScene) = NULL;
	}
	else {
		if (addSceneToMap) {
			AddScene(sceneName, altScene);
			ChangeScene(sceneName, nullptr);
		}
		else {
			current = SceneSet(sceneName, altScene);
			changed = true;
		}
	}
	if (changed) {
		Update();
		std::rotate(sceneHistory.rbegin(), sceneHistory.rbegin() + 1, sceneHistory.rend());
		sceneHistory[0] = SceneSet(current.sceneName, current.scene);
		sceneHistoryPosition = 0;
		header->SetSubtitle(current.sceneName);
	}
	return true;
}

bool SceneManager::ChangeSceneBackward()
{
	sceneHistoryPosition++;
	if (sceneHistoryPosition >= ApplicationPreference::sceneHistories)
		sceneHistoryPosition = ApplicationPreference::sceneHistories - 1;
	if (sceneHistory[sceneHistoryPosition].sceneName == blankScene.sceneName) {
		sceneHistoryPosition--;
		if (sceneHistoryPosition < 0) sceneHistoryPosition = 0;
		return false;
	}
	current = SceneSet(sceneHistory[sceneHistoryPosition].sceneName, sceneHistory[sceneHistoryPosition].scene);
	header->SetSubtitle(current.sceneName);
	return true;
}

bool SceneManager::ChangeSceneForward()
{
	sceneHistoryPosition--;
	if (sceneHistoryPosition < 0) sceneHistoryPosition = 0;
	if (sceneHistory[sceneHistoryPosition].sceneName == blankScene.sceneName) {
		sceneHistoryPosition++;
		if (sceneHistoryPosition >= ApplicationPreference::sceneHistories) sceneHistoryPosition = ApplicationPreference::sceneHistories - 1;
		return false;
	}
	current = SceneSet(sceneHistory[sceneHistoryPosition].sceneName, sceneHistory[sceneHistoryPosition].scene);
	header->SetSubtitle(current.sceneName);
	return true;
}

bool SceneManager::UpdateForwardBackwardScene(int forwardButton, int forwardFrame, int backwardButton, int backwardFrame)
{
	if (forwardButton == forwardFrame) {
		ChangeSceneForward();
	}
	if (backwardButton == backwardFrame) {
		ChangeSceneBackward();
	}
	return false;
}

void SceneManager::Collide()
{
	ObjectOverlapping::Reset();
	current.scene->Collide();
	header->Collide();
	popupScene->Collide();
}

void SceneManager::Update() {
	current.scene->Update();
	header->Update();
	popupScene->Update();
}

void SceneManager::Draw() {
	current.scene->Draw();
	header->Draw();
	popupScene->Draw();
}