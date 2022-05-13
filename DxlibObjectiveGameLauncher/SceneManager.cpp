#include "SceneManager.h"

SceneManager::SceneManager() {
	currentScene = new DebugScene();
}

SceneManager::~SceneManager() {
	delete(currentScene);
}

void SceneManager::Update() {
	currentScene->Update();
}

void SceneManager::Draw() {
	currentScene->Draw();
}