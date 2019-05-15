#pragma once

#include "task.hpp"
#include "scene_changer_interface.hpp"

#ifndef INCLUDE_SCENEMANAGER_HPP
#define INCLUDE_SCENEMANAGER_HPP


class Scene;

class SceneManager : public Task, public SceneChangerInterface
{
	Scene *scenes[numScene];
	Scene *currentScene;

public:
	SceneManager(HWND hWnd, SceneName firstScene, unsigned short bmpWidth, unsigned short bmpHeight);
	~SceneManager();
	int initialize();
	int finalize();
	int paint();
	int mouseMove(unsigned short x, unsigned short y, unsigned int param);
	int buttonLDown(unsigned short x, unsigned short y);
	int buttonLUp(unsigned short x, unsigned short y);
	int buttonRDown(unsigned short x, unsigned short y);
	int buttonRUp(unsigned short x, unsigned short y);
	int update();
	int changeScene(SceneName nextScene);
};


#endif