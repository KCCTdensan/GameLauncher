#pragma once

#include "SceneData.hpp"
#include "AppData.h"
#include "OperationData.h"
#include "MusicManager.h"
#include "PictureManager.h"
#include "JsonManager.h"

using namespace App;

class HEADER_Scene
{
public:
	HEADER_Scene(ObjectManager &objectManager, MusicManager &musicManager, Json &json, JsonManager& jsonManager, PictureManager& pictureManager);

	void Update();
	void Draw();

private:

	void AllHide();

	ObjectManager* objectManager;
	MusicManager* musicManager;
	PictureManager* pictureManager;
	Json* json;

	Json defJson = {
		"NONE",
		"",
		"",
		"",
		"NONE"
	};

	bool PlayingNotice;
	string PlayingName;

	int clickCount = 0;

	bool PlayingPicture;
};

