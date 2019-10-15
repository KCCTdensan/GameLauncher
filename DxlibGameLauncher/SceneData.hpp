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
	virtual void Update() = 0;
	
	virtual void Draw() = 0;
	
};