#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include "JsonManager.h"
#include "InputManager.h"


class TAB_OTHERS_Scene :
	public SceneData
{
public:
	TAB_OTHERS_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager);

	void Update();
	void Draw();
private:

	void MoveObj(int size);

	array<Json, 64>jsonOthers;

	bool canScroll;

	int scrollCurrentPos = 0;
	int scrollCurrentPosBefore = 0;

	JsonManager* jsonMan;

};