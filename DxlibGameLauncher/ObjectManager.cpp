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

int ObjectManager::Set(string stg, int x, int y, int sizeX, int sizeY)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag) continue;

		object[i].ExistenceFlag = TRUE;
		object[i].EffectiveFlag = TRUE;

		object[i].x = x;
		object[i].y = y;
		object[i].xSize = sizeX;
		object[i].ySize = sizeY;

	}
	return 0;
}

int ObjectManager::ColorSet(string stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].outsideFlag = outsideFlag;
		object[i].insideFlag = insideFlag;
		object[i].outsideColor = outsideColor;
		object[i].insideColor = insideColor;
		object[i].outsidePixel = outsideSize;

		re_num = 0;
	}

	return re_num;
}

int ObjectManager::RoundnessSet(string stg, bool flag, int size)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].RoundnessFlag = flag;
		object[i].RoundnessSize = size;

	}
	return 0;
}

int ObjectManager::WritingSet(string stg, bool flag, string data)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].WritingFlag = flag;
		object[i].writing = data;
	}
	return 0;
}

int ObjectManager::WritingFontSet(string stg, int font, int color,int arrengement)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].writingFont = font;
		object[i].writingColor = color;
		object[i].WritingArrengement = arrengement;
		
		re_num = 0;


	}

	return re_num;
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
