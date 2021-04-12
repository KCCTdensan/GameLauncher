#pragma once
#include "SceneProc.h"
class SceneProcHome :
    public SceneProc
{
public:
	SceneProcHome(ObjectManager& objectManager, Json& json, JsonManager& jsonManager, SCENE scenes);

	void Update();
	void Draw();
private:

	void MoveObj(int size);

	array<Json, 64>jsonData;

	Json* curJson;

	int objNum;

	bool canScroll;

	int scrollCurrentPos = 0;
	int scrollCurrentPosBefore = 0;

	SCENE* SceneNum;

	JsonManager* jsonMan;
	ObjectManager* objMan;
};

