#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include <array>
#include "JsonManager.h"
using namespace std;


class TAB_OTHERS_Scene :
	public SceneData
{
public:
	TAB_OTHERS_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager);

	void Update();
	void Draw();
private:
	array<Json, 64>jsonOthers;

};