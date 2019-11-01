#pragma once

#include "ObjectManager.h"
#include "JsonFileData.h"

class SceneData
{
protected:
	ObjectManager &objectManager;
	Json& json;
public:
	SceneData(ObjectManager &objectManager , Json &json)
		:objectManager(objectManager),json(json)
	{

	}
	virtual void Update() = 0;
	
	virtual void Draw() = 0;
	
};