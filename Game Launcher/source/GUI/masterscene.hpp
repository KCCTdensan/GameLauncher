#pragma once

#include "scene.hpp"

#ifndef INCLUDE_MASTERSCENE_HPP
#define INCLUDE_MASTERSCENE_HPP


enum SceneName
{
	Scene_StartUp,
	Scene_MainMenu,
	NumSceneName
};

class MasterScene :public Scene
{
	Scene*Scenes[NumSceneName];
	Scene*CurrentScene;

public:
	MasterScene(HWND hWnd, SceneName FirstScene, unsigned short BmpWidth, unsigned short BmpHeight);
	~MasterScene();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int Paint(HWND hWnd);
	int ChangeScene(HWND hWnd, int NextScene);
};


#endif