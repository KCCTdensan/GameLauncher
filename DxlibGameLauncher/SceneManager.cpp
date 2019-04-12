#include "SceneManager.h"
#include "DxLib.h"


SceneData *SceneManager::currentScene = NULL;
//SceneData *SceneManager::currentSceneLoad = new LoadScene();

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
	case SCENE::WINDOWSIZECHANGE:
		currentScene = new WindowSizeChangeScene();
		i = TRUE;
		break;
	case SCENE::TITLE:
		currentScene = new TitleScene();
		i = TRUE;
		break;
	case SCENE::GAMEPLAY:
		currentScene = new GamePlayScene();
		i = TRUE;
		break;
	case SCENE::LOADFILE:
		currentScene = new LoadFileScene();
		i = TRUE;
		break;
	default:
		i = FALSE;
		Ope::APPLICATION_END_FLAG = TRUE;
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
