#pragma once

#include "Scene/Task.hpp"
#include "Scene/SceneChangerInterface.hpp"

#ifndef INCLUDE_SCENEMANAGER_HPP
#define INCLUDE_SCENEMANAGER_HPP


class Scene;

class SceneManager :public Task, public SceneChangerInterface
{
	Scene*Scenes[NumSceneName];
	Scene*CurrentScene;

public:
	SceneManager(HWND hWnd, SceneName FirstScene, unsigned short BmpWidth, unsigned short BmpHeight);
	~SceneManager();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int Paint(HWND hWnd);
	int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp);
	int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
	int ChangeScene(HWND hWnd, SceneName NextScene);
};


#endif