#pragma once

#include "SceneData.hpp"
#include "JsonFileData.h"
#include <array>
using namespace std;

class TAB_MUSIC_Scene :
	public SceneData
{
public:
	TAB_MUSIC_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();
private:
	array<Json, 64>jsonMusic;

};