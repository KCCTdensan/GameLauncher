#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include <array>
#include "JsonManager.h"
using namespace std;


class TAB_APP_Scene :
	public SceneData
{
public:
	TAB_APP_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager);

	void Update();
	void Draw();
private:
	array<Json, 64>jsonApp;

};