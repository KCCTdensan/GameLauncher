#pragma once

#include "SceneData.hpp"
#include "AppData.h"

using namespace App;

class HEADER_Scene
{
public:
	HEADER_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();
};

