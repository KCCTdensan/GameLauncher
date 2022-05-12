#include "..\DxlibObjectiveGameLauncher\SceneManager.h"
#include "SceneManager.hpp"
#include "DxLib.h"


SceneManager::SceneManager(ObjectManager &objectManager, Json& json, JsonManager& jsonManager)
	: currentScene(nullptr)
{
	sceneSave[(int)SCENE::TAB_HOME]		= new SceneProcHome(objectManager, json, jsonManager, SCENE::TAB_HOME);
	sceneSave[(int)SCENE::TAB_APP]		= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_APP);
	sceneSave[(int)SCENE::TAB_GAME]		= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_GAME);
	sceneSave[(int)SCENE::TAB_MUSIC]	= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_MUSIC);
	sceneSave[(int)SCENE::TAB_3DMODEL]	= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_3DMODEL);
	sceneSave[(int)SCENE::TAB_VIDEO]	= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_VIDEO);
	sceneSave[(int)SCENE::TAB_PICTURE]	= new SceneProc(objectManager, json, jsonManager, SCENE::TAB_PICTURE);
}

SceneManager::SceneManager()
{
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

	case SCENE::TAB_PICTURE:
		currentScene = sceneSave[(int)SCENE::TAB_PICTURE];
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
