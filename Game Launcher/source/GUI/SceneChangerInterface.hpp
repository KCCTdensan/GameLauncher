#pragma once

#include <Windows.h>

#ifndef INCLUDE_SCENECHANGERINTERFACE_HPP
#define INCLUDE_SCENECHANGERINTERFACE_HPP


enum SceneName
{
	SceneName_MainMenu,
	SceneName_AppGallery,
	SceneName_GameGallery,

	NumSceneName
};

class SceneChangerInterface
{
public:
	virtual int ChangeScene(HWND hWnd, SceneName NextScene) = 0;
};


#endif