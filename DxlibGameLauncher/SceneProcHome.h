#pragma once
#include "SceneProc.h"
class SceneProcHome :
    public SceneProc
{
public:
	SceneProcHome(ObjectManager& objectManager, Json& json, JsonManager& jsonManager, SCENE scenes);

	virtual void Update();
private:
	void AllHide();
};

