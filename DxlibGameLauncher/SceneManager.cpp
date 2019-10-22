#include "SceneManager.hpp"
#include "DxLib.h"


SceneManager::SceneManager(SCENE firstScene, ObjectManager &objectManager)
	: currentScene(nullptr)
{
	sceneSave[TAB_HOME]		= new TAB_HOME_Scene(objectManager);
	sceneSave[TAB_APP]		= new TAB_APP_Scene(objectManager);
	sceneSave[TAB_GAME]		= new TAB_GAME_Scene(objectManager);
	sceneSave[TAB_MUSIC]	= new TAB_MUSIC_Scene(objectManager);
	sceneSave[TAB_3DMODEL]	= new TAB_3DMODEL_Scene(objectManager);
	sceneSave[TAB_VIDEO]	= new TAB_VIDEO_Scene(objectManager);
	sceneSave[TAB_OTHERS]	= new TAB_OTHERS_Scene(objectManager);

	ChanegeScene(firstScene);
}

SceneManager::~SceneManager()
{
	currentScene = nullptr;
	for(int i = 0; i < SCENE_NUM; i++)
	{
		delete sceneSave[i];
	}
}

int SceneManager::ChanegeScene(SCENE scene)
{
	switch(scene)
	{
	case TAB_HOME:
		currentScene = sceneSave[TAB_HOME];
		return TRUE;

	case TAB_APP:
		currentScene = sceneSave[TAB_APP];
		return TRUE;

	case TAB_GAME:
		currentScene = sceneSave[TAB_GAME];
		return TRUE;

	case TAB_MUSIC:
		currentScene = sceneSave[TAB_MUSIC];
		return TRUE;

	case TAB_3DMODEL:
		currentScene = sceneSave[TAB_3DMODEL];
		return TRUE;

	case TAB_VIDEO:
		currentScene = sceneSave[TAB_VIDEO];
		return TRUE;

	case TAB_OTHERS:
		currentScene = sceneSave[TAB_OTHERS];
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
