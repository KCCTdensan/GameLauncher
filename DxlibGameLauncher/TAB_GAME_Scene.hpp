#pragma once

#include "SceneData.hpp"


class TAB_GAME_Scene :
	public SceneData
{
public:
	TAB_GAME_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();
};