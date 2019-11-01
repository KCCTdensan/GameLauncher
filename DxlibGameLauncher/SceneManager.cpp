#include "SceneManager.hpp"
#include "DxLib.h"


SceneManager::SceneManager(ObjectManager &objectManager, Json& json)
	: currentScene(nullptr)
{
	sceneSave[(int)SCENE::TAB_HOME]		= new TAB_HOME_Scene(objectManager,json);
	sceneSave[(int)SCENE::TAB_APP]		= new TAB_APP_Scene(objectManager, json);
	sceneSave[(int)SCENE::TAB_GAME]		= new TAB_GAME_Scene(objectManager, json);
	sceneSave[(int)SCENE::TAB_MUSIC]	= new TAB_MUSIC_Scene(objectManager, json);
	sceneSave[(int)SCENE::TAB_3DMODEL]	= new TAB_3DMODEL_Scene(objectManager, json);
	sceneSave[(int)SCENE::TAB_VIDEO]	= new TAB_VIDEO_Scene(objectManager, json);
	sceneSave[(int)SCENE::TAB_OTHERS]	= new TAB_OTHERS_Scene(objectManager, json);
}

SceneManager::~SceneManager()
{
	for(int i = 0; i < (int)SCENE::SCENE_NUM; i++)
	{
		delete sceneSave[i];
	}
}

int SceneManager::ChanegeScene(SCENE scene)
{
	switch(scene)
	{
	case SCENE::TAB_HOME:
		currentScene = sceneSave[(int)SCENE::TAB_HOME];
		return TRUE;

	case SCENE::TAB_APP:
		currentScene = sceneSave[(int)SCENE::TAB_APP];
		return TRUE;

	case SCENE::TAB_GAME:
		currentScene = sceneSave[(int)SCENE::TAB_GAME];
		return TRUE;

	case SCENE::TAB_MUSIC:
		currentScene = sceneSave[(int)SCENE::TAB_MUSIC];
		return TRUE;

	case SCENE::TAB_3DMODEL:
		currentScene = sceneSave[(int)SCENE::TAB_3DMODEL];
		return TRUE;

	case SCENE::TAB_VIDEO:
		currentScene = sceneSave[(int)SCENE::TAB_VIDEO];
		return TRUE;

	case SCENE::TAB_OTHERS:
		currentScene = sceneSave[(int)SCENE::TAB_OTHERS];
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
