#pragma once

#include "scene/TAB_APP_Scene.hpp"
#include "scene/TAB_GAME_Scene.hpp"
#include "scene/TAB_HOME_Scene.hpp"
#include "scene/TAB_MUSIC_Scene.hpp"
#include <array>


enum SceneID
{
	TAB_HOME,
	TAB_APP,
	TAB_GAME,
	TAB_MUSIC,
	SCENE_NUM
};

class SceneManager
{
	std::array<scene::SceneBase *, SCENE_NUM> scenes;
	scene::SceneBase *currentScene;

public:
	SceneManager(ObjectManager &objectManager);
	~SceneManager();

	int changeScene(SceneID sceneID);
	void update();
	void draw();
};