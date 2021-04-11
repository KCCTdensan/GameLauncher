#pragma once
#include "ObjectManager.h"
#include "JsonFileData.h"
#include "JsonManager.h"
#include "SceneList.h"

class SceneProc
{
public:
	SceneProc(ObjectManager& objectManager, Json& json, JsonManager& jsonManager, SCENE scenes);

	void Update();
	void Draw();
private:

	void MoveObj(int size);

	array<Json, 64>jsonData;

	Json *curJson;

	int objNum;

	bool canScroll;

	int scrollCurrentPos = 0;
	int scrollCurrentPosBefore = 0;

	SCENE *SceneNum;

	JsonManager* jsonMan;
	ObjectManager* objMan;
};
    