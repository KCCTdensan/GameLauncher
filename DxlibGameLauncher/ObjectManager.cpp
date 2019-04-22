#include "ObjectManager.h"

/*


	object[i].pictureHandleTmp;
	object[i].pictureHandle;

	object[i].WritingFlag = FALSE;
	object[i].writing;
	object[i].writingX;
	object[i].writingY;
	object[i].WritingWidth;

	object[i].writingColor;
	object[i].writingFont;
	object[i].ritingSize;

	object[i].ListFlag;
	object[i].ListArrengement;
	object[i].ListData[LIST_MAX];
	object[i].ListDataX[LIST_MAX];
	object[i].ListDataY[LIST_MAX];
	object[i].ListDataWidth[LIST_MAX];
	object[i].ListOneSizeheight[LIST_MAX];



*/

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

int ObjectManager::ObjectSetup(string stg, int x, int y, int sizeX, int sizeY)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag) continue;

		object[i].ExistenceFlag = TRUE;
		object[i].EffectiveFlag = TRUE;

		object[i].x;
		object[i].y;
		object[i].xSize;
		object[i].ySize;

	}
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
