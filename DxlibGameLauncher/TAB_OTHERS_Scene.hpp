#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include <array>
using namespace std;


class TAB_OTHERS_Scene :
	public SceneData
{
public:
	TAB_OTHERS_Scene(ObjectManager &objectManager, Json& json);

	void Update();
	void Draw();
private:
	array<Json, 64>jsonOthers;

};