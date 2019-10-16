#include "ObjectManager.h"
#include "AppData.h"
#include "InputManager.h"


ObjectManager::ObjectManager()
{
}

int ObjectManager::Set(wstring stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type)
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

		object[i].ObjectType = type;

		break;
	}
	return 0;
}

int ObjectManager::ColorSet(wstring stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].outsideFlag = outsideFlag;
		object[i].insideFlag = insideFlag;
		object[i].outsideColor = outsideColor;
		object[i].insideColor = insideColor;
		object[i].outsidePixel = outsideSize;

		re_num = 0;
	}

	return re_num;
}

int ObjectManager::RoundnessSet(wstring stg, bool flag, int size)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].RoundnessFlag = flag;
		object[i].RoundnessSize = size;

	}
	return 0;
}

int ObjectManager::WritingSet(wstring stg, bool flag, wstring data)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].WritingFlag = flag;
		object[i].writing = data;
	}
	return 0;
}

int ObjectManager::WritingFontSet(wstring stg, int font, int size, int color, int arrangementX, int arrangementY)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].writingFont = font;
		object[i].writingColor = color;
		object[i].WritingArrengementX = arrangementX;
		object[i].writingSize = size;

		re_num = 0;

		wstring a;

		switch (object[i].writingFont)
		{
		case OBJECT_FONT_GOTHIC:
			a = *App::FONT_GOTHIC;

			break;
		}

		object[i].FontHandle = CreateFontToHandle(a.c_str(), object[i].writingSize, -1, DX_FONTTYPE_ANTIALIASING);

		int len;

		switch (object[i].WritingArrengementX)
		{
		case ARRANGEMENT_X_LEFT:
			object[i].writingX = object[i].x + object[i].outsidePixel;
			break;
		case ARRANGEMENT_X_CENTER:
			len = static_cast<int>(lstrlen(object[i].writing.c_str()));
			object[i].WritingWidth = GetDrawStringWidthToHandle(object[i].writing.c_str(), len, object[i].FontHandle);
			object[i].writingX = object[i].x + (object[i].xSize - object[i].WritingWidth) / 2;
			break;
		case ARRANGEMENT_X_RIGHT:
			len = static_cast<int>(lstrlen(object[i].writing.c_str()));
			object[i].WritingWidth = GetDrawStringWidthToHandle(object[i].writing.c_str(), len, object[i].FontHandle);
			object[i].writingX = object[i].x + object[i].xSize - object[i].WritingWidth - object[i].outsidePixel;
			break;
		}
		switch (object[i].WritingArrengementY)
		{
		case ARRANGEMENT_Y_TOP:
			object[i].writingY = object[i].ySize;
			break;
		case ARRANGEMENT_Y_CENTER:
			object[i].writingY = object[i].y + ((object[i].ySize - object[i].writingSize) / 2);
			break;
		case ARRANGEMENT_Y_BOTTOM:
			object[i].writingY = object[i].y + object[i].ySize - object[i].writingSize;
			break;
		}
	}

	return re_num;
}

int ObjectManager::ImageChestSet(wstring stg, bool flag, wstring PicPath, int sizeX, int sizeY, int setX, int setY)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].pictureFlag = flag;
		if (flag == FALSE) {
			return 0;
		}

		object[i].pictureNumTmp = LoadGraph(PicPath.c_str());

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

		object[i].pictureX = setX;
		object[i].pictureY = setY;

		break;
	}

	return 0;
}

void ObjectManager::Update()
{
	Input::Mouse::Update();
	Input::KeyBoard::Update();

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag && !object[i].EffectiveFlag) continue;

		if (object[i].x <= Input::Mouse::MOUSE_WIN_X &&
			object[i].x + object[i].xSize >= Input::Mouse::MOUSE_WIN_X &&
			object[i].y <= Input::Mouse::MOUSE_WIN_Y &&
			object[i].y + object[i].ySize >= Input::Mouse::MOUSE_WIN_Y)
		{
			object[i].MouseFlag = TRUE;
			if (Input::Mouse::MOUSE_CLICK & MOUSE_INPUT_LEFT)
			{
				for (int j = 0;j < OBJECT_MAX;j++) {
					object[j].ActivationFlag = FALSE;

				}
				object[i].ActivationFlag = TRUE;
			}
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
		if (!object[i].ExistenceFlag) continue;//ŽlŠp•`‰æ or ‘È‰~

		switch (object[i].ObjectType) {

		case BUTTON:
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

			if (object[i].pictureFlag) {
				DrawGraph(object[i].x + object[i].pictureX, object[i].y + object[i].pictureY, object[i].pictureNum, TRUE);
			}

			if (object[i].WritingFlag) {
				DrawFormatStringToHandle(object[i].writingX, object[i].writingY, object[i].writingColor, object[i].FontHandle, object[i].writing.c_str());
			}


			if (object[i].MouseFlag && !object[i].ActivationFlag) {

			}
			if (object[i].ActivationFlag) {

			break;

		case PICTURE:

			DrawGraph(object[i].x + object[i].pictureX, object[i].y + object[i].pictureY, object[i].pictureNum, TRUE);

			break;

		}


	}

	// todo effect

	// todo writing





}

