#include "ObjectManager.h"
#include "AppData.h"


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

int ObjectManager::Set(tstring stg, int x, int y, int sizeX, int sizeY)
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

int ObjectManager::ColorSet(tstring stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor)
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

int ObjectManager::RoundnessSet(tstring stg, bool flag, int size)
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

int ObjectManager::WritingSet(tstring stg, bool flag, tstring data)
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

int ObjectManager::WritingFontSet(tstring stg, int font, int color, int arrengement)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].writingFont = font;
		object[i].writingColor = color;
		object[i].WritingArrengement = arrengement;

		re_num = 0;

		tstring a;

		switch (object[i].writingFont)
		{
		case OBJECT_FONT_GOTHIC:
			a = App::FONT_GOTHIC;

			break;
		}

		object[i].FontHandle = CreateFontToHandle(a.c_str(), object[i].writingSize, -1, DX_FONTTYPE_ANTIALIASING);

		int len;

		switch (object[i].WritingArrengement)
		{
		case ARRANGEMENT_LEFT:
			object[i].writingX = object[i].x + object[i].outsidePixel;
			break;
		case ARRANGEMENT_CENTER:
			len = (int)lstrlen(object[i].writing.c_str());
			object[i].WritingWidth = GetDrawStringWidthToHandle(object[i].writing.c_str(), len, object[i].FontHandle);
			object[i].writingX = object[i].x + (object[i].xSize - object[i].WritingWidth) / 2;
			break;
		case ARRANGEMENT_RIGHT:
			len = (int)lstrlen(object[i].writing.c_str());
			object[i].WritingWidth = GetDrawStringWidthToHandle(object[i].writing.c_str(), len, object[i].FontHandle);
			object[i].writingX = object[i].x + object[i].xSize - object[i].WritingWidth - object[i].outsidePixel;
			break;
		}
		object[i].writingY = object[i].y + (object[i].ySize - object[i].writingSize) / 2;
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
