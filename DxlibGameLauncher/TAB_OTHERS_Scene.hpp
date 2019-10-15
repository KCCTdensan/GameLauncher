#pragma once

#include "SceneData.hpp"


class TAB_OTHERS_Scene :
	public SceneData
{
public:
	TAB_OTHERS_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();
};