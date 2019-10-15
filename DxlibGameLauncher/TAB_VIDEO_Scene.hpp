#pragma once

#include "SceneData.hpp"


class TAB_VIDEO_Scene :
	public SceneData
{
public:
	TAB_VIDEO_Scene(ObjectManager &objectManager);

	void Update();
	void Draw();
};

