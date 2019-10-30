#pragma once

#include "SceneData.hpp"
#include "AppData.h"
#include "OperationData.h"
#include "MusicManager.h"

using namespace App;

class HEADER_Scene
{
public:
	HEADER_Scene(ObjectManager &objectManager, MusicManager &musicManager);

	void Update();
	void Draw();

private:

	void AllHide();

	ObjectManager* objectManager;
	MusicManager* musicManager;

	bool PlayingNotice;
};

