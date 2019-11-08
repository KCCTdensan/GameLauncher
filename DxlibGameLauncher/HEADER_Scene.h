#pragma once

#include "SceneData.hpp"
#include "AppData.h"
#include "OperationData.h"
#include "MusicManager.h"
#include "JsonManager.h"

using namespace App;

class HEADER_Scene
{
public:
	HEADER_Scene(ObjectManager &objectManager, MusicManager &musicManager, Json &json, JsonManager& jsonManager);

	void Update();
	void Draw();

private:

	void AllHide();

	ObjectManager* objectManager;
	MusicManager* musicManager;
	Json* json;

	Json defJson;

	bool PlayingNotice;
	string PlayingName;
};

