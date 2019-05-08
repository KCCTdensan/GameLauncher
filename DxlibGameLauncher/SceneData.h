#pragma once

#include <DxLib.h>


class SceneData
{
public:
	SceneData();
	~SceneData();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};