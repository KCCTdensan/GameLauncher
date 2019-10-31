#pragma once

#include "SceneData.hpp"
#include "InputManager.h"
#include "JsonFileData.h"
#include <array>

class TAB_HOME_Scene :
	public SceneData
{
public:
	TAB_HOME_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();

private:
	array<Json, 64>jsonHome;
};