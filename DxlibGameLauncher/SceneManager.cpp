#include "sce"



SceneManager::SceneManager(ObjectManager &objectManager)
	: objectManager(objectManager), currentScene(nullptr)
{
	//quitFlag = FALSE;
}

SceneManager::~SceneManager()
{
	delete currentScene;
}

int SceneManager::ChanegeScene(SCENE scene)
{
	if(currentScene != nullptr)
	{
		delete currentScene;
	}
	switch(scene)
	{
	case TAB_HOME:
		currentScene = new TAB_HOME_Scene(objectManager);
		return TRUE;

	case TAB_APP:
		currentScene = new TAB_APP_Scene(objectManager);
		return TRUE;

	case TAB_GAME:
		currentScene = new TAB_GAME_Scene(objectManager);
		return TRUE;

	case TAB_MUSIC:
		currentScene = new TAB_MUSIC_Scene(objectManager);
		return TRUE;

	default:
		return FALSE;
	}
}

void SceneManager::Update()
{
	currentScene->Update();
}

void SceneManager::Draw()
{
	currentScene->Draw();
}
