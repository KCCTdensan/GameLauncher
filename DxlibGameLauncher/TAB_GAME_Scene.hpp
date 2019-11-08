#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include "JsonManager.h"

class TAB_GAME_Scene :
	public SceneData
{
public:
	TAB_GAME_Scene(ObjectManager& objectManager, Json& json, JsonManager& jsonManager);

	void Update();
	void Draw();

private:

	array<Json, 64>jsonGame;

};