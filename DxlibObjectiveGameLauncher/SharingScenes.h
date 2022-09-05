#pragma once
#include "SceneBase.h"

struct SharingScenes
{
	SceneBase* header;

	SharingScenes(SceneBase* _header)
		: header(_header) {}

	SharingScenes()
		: header(nullptr) {}
};

