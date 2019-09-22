#pragma once

#include "ObjectManager.h"


class SceneData
{
protected:
	ObjectManager &objectManager;

public:
	SceneData(ObjectManager &objectManager)
		:objectManager(objectManager)
	{

	}
	virtual void Update()
	{
		objectManager.Update();
	}
	virtual void Draw()
	{
		objectManager.Draw();
	}
};