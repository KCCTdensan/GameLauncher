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

bool SceneManager::ChangeScene(std::string sceneName, SceneBase* altScene, bool addSceneToMap, bool deleteNotAddedScene)
{
	bool changed = false;
	//if (!isAddingMap && SceneManager::deleteNotAddedScene)
	//	delete(current.scene);
	if (scenes.count(sceneName) >= 1) {
		//if (current.sceneName == sceneName)
		//	deleteNotAddedScene = false;
		current = SceneSet(sceneName, scenes[sceneName]);
		changed = true;
		if (deleteNotAddedScene)
			delete(altScene);
		//delete (altScene); (altScene) = NULL;
	}
	else {
		if (addSceneToMap) {
			AddScene(sceneName, altScene);
			ChangeScene(sceneName, nullptr, true, false);
		}
		else {
			current = SceneSet(sceneName, altScene);
			changed = true;
		}
	}
	if (changed) {
		Update();
		//std::rotate(sceneHistory.rbegin(), sceneHistory.rbegin() + 1, sceneHistory.rend());
		for (int i = 0; i < sceneHistoryPosition; i++) {
			std::rotate(sceneHistory.begin(), sceneHistory.begin() + sceneHistoryPosition, sceneHistory.end());
			if (!sceneHistory[sceneHistory.size() - 1].addSceneToMap && sceneHistory[sceneHistory.size() - 1].deleteNotAddedScene) {
				bool isExisting = false;
				for (int i = (int)sceneHistory.size() - 2; i >= 0; i--) {
					if (sceneHistory[i].scene == sceneHistory[sceneHistory.size()-1].scene) {
						isExisting = true;
						break;
					}
				}
				if (!isExisting) delete sceneHistory[sceneHistory.size() - 1].scene;
			}
			sceneHistory[sceneHistory.size() - 1] = blankScene;
		}
		sceneHistoryPosition = 0;
		std::rotate(sceneHistory.rbegin(), sceneHistory.rbegin() + 1, sceneHistory.rend());
		if (!sceneHistory[0].addSceneToMap && sceneHistory[0].deleteNotAddedScene) {
			bool isExisting = false;
			for (int i = 1; i < sceneHistory.size(); i++) {
				if (sceneHistory[i].scene == sceneHistory[0].scene) {
					isExisting = true;
					break;
				}
			}
			if (!isExisting) delete sceneHistory[0].scene;
		}
		sceneHistory[0] = SceneSet(current.sceneName, current.scene, addSceneToMap, deleteNotAddedScene);
		header->SetSubtitle(current.sceneName);

		/*if (scenes.size() > 4) {
			delete(scenes.begin()->second);
			scenes.erase(scenes.begin());
		}*/
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