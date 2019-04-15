#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		object[i].ExistenceFlag = FALSE;
	}
}


ObjectManager::~ObjectManager()
{
}

int ObjectManager::ObjectSetup(string stg, int x, int y, int sizeX, int sizeY, bool AnimationFlag)
{
	return 0;
}

int ObjectManager::ObjectColorSetup(string stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor)
{
	return 0;
}

int ObjectManager::ObjectRoundnessSetup(string stg, bool flag, int size)
{
	return 0;
}

void ObjectManager::Update()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag) continue;
	}
}

void ObjectManager::Draw()
{
}
