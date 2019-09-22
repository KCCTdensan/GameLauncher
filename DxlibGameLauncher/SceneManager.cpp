#include "SceneManager.h"
#include "DxLib.h"

using namespace std;
SceneData *SceneManager::currentScene = NULL;
SceneData* scenes[SCENE_NUM];


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	delete currentScene;
}

int SceneManager::ChanegeScene(SCENE scene)
{
	if(currentScene != NULL)
	{
		delete currentScene;
	}
	bool i = FALSE;

	switch(scene)
	{
	case TAB_HOME:
		currentScene = new TAB_HOME_Scene();
		i = TRUE;
		break;
	case TAB_APP:
		currentScene = new TAB_APP_Scene();
		i = TRUE;
		break;
	case TAB_GAME:
		currentScene = new TAB_GAME_Scene();
		i = TRUE;
		break;
	case TAB_MUSIC:
		currentScene = new TAB_MUSIC_Scene();
		i = TRUE;
		break;
	default:
		i = FALSE;
		break;
	}
	return i;
}

void SceneManager::Update()
{
	currentScene->Update();

	return;
}

void SceneManager::Draw()
{
	currentScene->Draw();

	return;
}
