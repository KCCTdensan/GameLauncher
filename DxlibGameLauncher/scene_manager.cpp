#include "scene_manager.hpp"
#include <DxLib.h>


SceneManager::SceneManager(ObjectManager &objectManager)
	: currentScene(nullptr)
{
	scenes[TAB_HOME] = new scene::TAB_HOME_Scene(objectManager);
	scenes[TAB_APP] = new scene::TAB_APP_Scene(objectManager);
	scenes[TAB_GAME] = new scene::TAB_GAME_Scene(objectManager);
	scenes[TAB_MUSIC] = new scene::TAB_MUSIC_Scene(objectManager);

	currentScene = scenes[TAB_HOME];
	currentScene->initialize();
}

SceneManager::~SceneManager()
{
	for(scene::SceneBase *scene : scenes)
	{
		delete scene;
	}
}

void SceneManager::changeScene(SceneID sceneID)
{
	currentScene->finalize();
	currentScene = scenes[sceneID];
	currentScene->initialize();
}

void SceneManager::update()
{
	currentScene->update();
}

void SceneManager::draw()
{
	currentScene->draw();
}
