#include "SceneManager.h"
#include "DxLib.h"
#include "MainScene.h"

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
	case MAIN:
		currentScene = new MainScene();
		i = TRUE;
		break;
	
	default:
		i = FALSE;
		
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