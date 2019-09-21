#include "ObjectManager.h"
#include "AppData.h"
#include "InputManager.h"


/*


		int ObjectType;

	tstring name;

	bool ExistenceFlag = FALSE;//存在フラグ
	bool EffectiveFlag = TRUE;//有効フラグ

	bool ActivationFlag;
	bool MouseFlag;

	int AnimationBlend;
	bool AnimationFlag;
	int AnimationTick = 0;

	bool RoundnessFlag;
	int RoundnessSize;

	int x;
	int y;
	int xSize;
	int ySize;

	bool insideFlag;
	bool outsideFlag;
	int insideColor;
	int outsideColor;
	int outsidePixel;

	bool pictureFlag;
	int pictureEnum;

	bool WritingFlag = FALSE;
	tstring writing;
	int writingX;
	int writingY;
	int WritingWidth;

	int writingColor;
	int writingFont;
	int writingSize;

	int FontHandle;

	int WritingArrengement;

	bool ListFlag;
	tstring ListData[LIST_MAX];
	int ListDataX[LIST_MAX];
	int ListDataY[LIST_MAX];
	int ListDataWidth[LIST_MAX];
	int ListOneSizeheight[LIST_MAX];

	変数一覧です。現在のobjectdata一つずつに入ってるものです

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

		object[i].name = stg;

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

int ObjectManager::ImageChestSet(tstring stg, bool flag, TCHAR PicPath, int sizeX, int sizeY)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (object[i].ExistenceFlag && object[i].name != stg) continue;

		object[i].pictureFlag = flag;
		if (flag == FALSE) {
			return 0;
		}

		object[i].pictureNumTmp = LoadGraph(&PicPath);

		int getSizeX, getSizeY;
		GetGraphSize(object[i].pictureNumTmp, &getSizeX, &getSizeY);
		if (getSizeX != sizeX || getSizeY != sizeY)
		{
			object[i].pictureNum = MakeScreen(sizeX, sizeY, TRUE);
			if (object[i].pictureNum == -1) {
				DeleteGraph(object[i].pictureNumTmp);
				return -1;
			}
			SetDrawScreen(object[i].pictureNum);
			DrawExtendGraph(0, 0, sizeX, sizeY, object[i].pictureNumTmp, TRUE);
			DeleteGraph(object[i].pictureNumTmp);
		}
		else {
			object[i].pictureNum = object[i].pictureNumTmp;

		}
		
		break;
	}

	return 0;
}

void ObjectManager::Update()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag && !object[i].EffectiveFlag) continue;

		if (object[i].x <= Input::Mouse::MOUSE_WIN_X &&
			object[i].x + object[i].xSize >= Input::Mouse::MOUSE_WIN_X &&
			object[i].y <= Input::Mouse::MOUSE_WIN_Y &&
			object[i].y + object[i].ySize >= Input::Mouse::MOUSE_WIN_Y)
		{
			object[i].MouseFlag = TRUE;

			//todo hit
		}
		else {
			object[i].MouseFlag = FALSE;
		}

	}
}

void ObjectManager::Draw()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag) continue;//四角描画 or 楕円

		switch (object[i].pictureFlag)
		{
		case FALSE:
			switch (object[i].RoundnessFlag)
			{
			case TRUE:
				if (object[i].outsideFlag) {
					DrawRoundRect(object[i].x, object[i].y, object[i].x + object[i].xSize, object[i].y + object[i].ySize, object[i].RoundnessSize, object[i].RoundnessSize, object[i].outsideColor, TRUE);
				}
				if (object[i].insideFlag) {
					DrawRoundRect(object[i].x - object[i].outsidePixel, object[i].y - object[i].outsidePixel, object[i].xSize + object[i].x - object[i].outsidePixel, object[i].ySize + object[i].y - object[i].outsidePixel, object[i].RoundnessSize, object[i].RoundnessSize, object[i].insideColor, TRUE);
				}
				break;
			case FALSE:
				if (object[i].outsideFlag) {
					DrawBox(object[i].x, object[i].y, object[i].xSize + object[i].x, object[i].ySize + object[i].y, object[i].outsideColor, TRUE);
				}
				if (object[i].insideFlag)
				{
					DrawBox(object[i].x + object[i].outsidePixel, object[i].y + object[i].outsidePixel, object[i].xSize + object[i].x - object[i].outsidePixel, object[i].ySize + object[i].y - object[i].outsidePixel, object[i].insideColor, TRUE);
				}
			}
			break;
		case TRUE:
			break;
		}

		// todo effect

		// todo writing





	}

}