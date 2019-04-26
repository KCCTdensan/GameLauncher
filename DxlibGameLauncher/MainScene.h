#pragma once
#include "SceneData.h"
class MainScene :
	public SceneData
{
public:
	MainScene();
	~MainScene();

	void Update();
	void Draw();
};

