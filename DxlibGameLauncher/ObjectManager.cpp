#include "ObjectManager.h"
#include "AppData.h"
#include "InputManager.h"


ObjectManager::ObjectManager()
{
}

int ObjectManager::Set(string stg, int x, int y, int sizeX, int sizeY, OBJECT_TYPE type)
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

int ObjectManager::ColorSet(string stg, bool outsideFlag, int outsideColor, int outsideSize, bool insideFlag, int insideColor)
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

		break;
	}

	return re_num;
}

int ObjectManager::RoundnessSet(string stg, bool flag, int size)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].RoundnessFlag = flag;
		object[i].RoundnessSize = size;

		break;
	}
	return 0;
}

int ObjectManager::WritingSet(string stg, bool flag, string data)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].WritingFlag = flag;
		object[i].writing = data;

		break;
	}
	return 0;
}

int ObjectManager::WritingFontSet(string stg, int font, int size, int color, int arrangementX, int arrangementY)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].writingFont = font;
		object[i].writingColor = color;
		object[i].WritingArrengementX = arrangementX;
		object[i].WritingArrengementY = arrangementY;
		object[i].writingSize = size;

		re_num = 0;

		string a;

		switch (object[i].writingFont)
		{
		case OBJECT_FONT_GOTHIC:
			a = App::FONT_GOTHIC;

			break;
		}

		object[i].FontHandle = CreateFontToHandle(a.c_str(), object[i].writingSize, -1, DX_FONTTYPE_ANTIALIASING);

		object[i].fontOwnFlag = TRUE;

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

		break;
	}

	return re_num;
}

int ObjectManager::WritingFontSetToHandle(string stg, string handleName, int Color, int arrangementX, int arrangementY)
{
	int re_num = -1;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].writingColor = Color;
		object[i].WritingArrengementX = arrangementX;
		object[i].WritingArrengementY = arrangementY;

		re_num = 0;

		int bufSize = 15;

		for (int j = 0;j < FONT_HANDLE_MAX;j++)
		{
			if (!fontData[j].ActiveFlag || fontData[j].name != handleName) continue;

			object[i].fontOwnFlag = FALSE;

			object[i].FontHandle = fontData[j].handle;
			bufSize = fontData[j].size;

		}

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
			object[i].writingY = object[i].y + ((object[i].ySize - bufSize) / 2);
			break;
		case ARRANGEMENT_Y_BOTTOM:
			object[i].writingY = object[i].y + object[i].ySize - bufSize;
			break;
		}

		break;
	}

	return re_num;
}

int ObjectManager::ImageChestSet(string stg, bool flag, string PicPath, int setX, int setY)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		object[i].pictureFlag = flag;
		if (flag == FALSE) {
			return 0;
		}

		object[i].pictureNumTmp = LoadGraph(PicPath.c_str());

		/*int getSizeX, getSizeY;
		GetGraphSize(object[i].pictureNumTmp, &getSizeX, &getSizeY);
		if (getSizeX != sizeX || getSizeY != sizeY)
		{
			object[i].pictureNum = MakeScreen(sizeX, sizeY, TRUE);
			if (object[i].pictureNum == -1) {
				DeleteGraph(object[i].pictureNumTmp);
				return -1;
			}
			SetDrawScreen(object[i].pictureNum);
			//DrawBox(0, 0, 100, 100, GetColor(255, 255, 255), TRUE);
			int we = DrawExtendGraph(0, 0, sizeX, sizeY, object[i].pictureNumTmp, TRUE);
			DeleteGraph(object[i].pictureNumTmp);
		}
		else {


		}

		‚±‚±‚ð‚Ç‚¤‚É‚©‚µ‚½‚¢

		*/

		object[i].pictureNum = object[i].pictureNumTmp;

		object[i].pictureX = setX;
		object[i].pictureY = setY;

		break;
	}

	return 0;
}

int ObjectManager::ProgressSet(string str, bool flag, int frontColor, int backColor, float startRate)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != str) continue;

		object[i].progressFlag = flag;
		object[i].progressRate = startRate;
		object[i].progressForwardColor = frontColor;
		object[i].progressBackColor = backColor;

		object[i].progressRange = (float)object[i].xSize * object[i].progressRate;
	}
	return 0;
}

int ObjectManager::ChangeProgress(string str, float rate)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != str) continue;

		object[i].progressRate = rate;

		object[i].progressRange = (float)object[i].xSize * object[i].progressRate;
	}
	return 0;
}

int ObjectManager::ChangeVarInt(string stg, VAR var, int num)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		switch (var)
		{
		case VAR::X:
			object[i].x = num;
			break;
		case VAR::Y:
			object[i].y = num;
			break;
		case VAR::SIZE_X:
			object[i].xSize = num;
			break;
		case VAR::SIZE_Y:
			object[i].ySize = num;
			break;
		case VAR::WRITING_X:
			object[i].writingX = num;
			break;
		case VAR::WRITING_Y:
			object[i].writingY = num;
			break;
		default:
			break;
		}

		break;
	}

	return 0;
}

int ObjectManager::ChangeVarBool(string stg, VAR var, bool flag)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		switch (var)
		{
		case VAR::EFFECTIVE_FLAG:
			object[i].EffectiveFlag = flag;
			break;
		case VAR::MOUSE_FLAG:
			object[i].MouseFlag = flag;
			break;
		case VAR::ANIMATION_FLAG:
			object[i].AnimationFlag = flag;
			break;
		case VAR::WRITING_FLAG:
			object[i].WritingFlag = flag;
			break;
		case VAR::CAN_SEE_FLAG:
			object[i].CanSeeFlag = flag;
			break;
		case VAR::ACTIVATION_FLAG:
			object[i].ActivationFlag = flag;
			break;
		default:
			break;
		}

		break;
	}

	return 0;
}

int ObjectManager::GetVarInt(string stg, VAR var)
{
	int num = -1;

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		switch (var)
		{
		case VAR::X:
			num = object[i].x;
			break;
		case VAR::Y:
			num = object[i].y;
			break;
		case VAR::SIZE_X:
			num = object[i].xSize;
			break;
		case VAR::SIZE_Y:
			num = object[i].ySize;
			break;
		case VAR::WRITING_X:
			num = object[i].writingX;
			break;
		case VAR::WRITING_Y:
			num = object[i].writingY;
			break;
		default:
			break;
		}

		break;
	}

	return num;
}

bool ObjectManager::GetVarBool(string stg, VAR var)
{

	bool flag = FALSE;

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (!object[i].ExistenceFlag || object[i].name != stg) continue;

		switch (var)
		{
		case VAR::EFFECTIVE_FLAG:
			flag = object[i].EffectiveFlag;
			break;
		case VAR::MOUSE_FLAG:
			flag = object[i].MouseFlag;
			break;
		case VAR::ANIMATION_FLAG:
			flag = object[i].AnimationFlag;
			break;
		case VAR::WRITING_FLAG:
			flag = object[i].WritingFlag;
			break;
		case VAR::ACTIVATION_FLAG:
			flag = object[i].ActivationFlag;
			break;
		case VAR::CAN_SEE_FLAG:
			flag = object[i].CanSeeFlag;
			break;
		default:
			break;
		}

		break;
	}

	return flag;
}

int ObjectManager::Delete(string stg)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{

		if (object[i].name != stg) continue;

		object[i].ExistenceFlag = FALSE;
		object[i].EffectiveFlag = FALSE;

		object[i].name = "";

		object[i].x = 0;
		object[i].y = 0;
		object[i].xSize = 1;
		object[i].ySize = 1;

		if (object[i].fontOwnFlag)
		{
			DeleteFontToHandle(object[i].FontHandle);
		}

		break;

	}
	return 0;
}

int ObjectManager::DeleteAll(void)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		object[i].ExistenceFlag = FALSE;
		object[i].EffectiveFlag = FALSE;

		object[i].name = "";

		object[i].x = 0;
		object[i].y = 0;
		object[i].xSize = 1;
		object[i].ySize = 1;

		if (object[i].fontOwnFlag)
		{
			DeleteFontToHandle(object[i].FontHandle);
		}

	}
	return 0;
}

int ObjectManager::HandleFontSet(string stg, int font, int size)
{
	for (int i = 0;i < FONT_HANDLE_MAX;i++)
	{
		if (fontData[i].ActiveFlag) continue;

		fontData[i].ActiveFlag = TRUE;

		fontData[i].name = stg;
		fontData[i].size = size;

		string a;

		switch (font)
		{
		case OBJECT_FONT_GOTHIC:
			a = App::FONT_GOTHIC;

			break;
		}

		fontData[i].handle = CreateFontToHandle(a.c_str(), fontData[i].size, -1, DX_FONTTYPE_ANTIALIASING);

		break;

	}


	return 0;
}

int ObjectManager::GetHandleFont(string stg)
{
	int num = 0;

	for (int i = 0;i < FONT_HANDLE_MAX;i++)
	{
		if (fontData[i].name != stg) continue;
		num = fontData[i].handle;

		break;
	}

	return num;
}

int ObjectManager::DeleteHandleFont(string stg)
{
	for (int i = 0;i < FONT_HANDLE_MAX;i++)
	{
		if (fontData[i].ActiveFlag)
		{
			if (fontData[i].handle != -1)
			{
				DeleteFontToHandle(fontData[i].handle);
			}
		}
	}

	return 0;
}

int ObjectManager::DeleteHandleFontAll(void)
{
	for (int i = 0;i < FONT_HANDLE_MAX;i++)
	{
		if (fontData[i].ActiveFlag)
		{
			if (fontData[i].handle != -1)
			{
				DeleteFontToHandle(fontData[i].handle);
			}
		}
	}
	return 0;
}

void ObjectManager::Update()
{

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		latestClick++;

		if (!object[i].ExistenceFlag && !object[i].EffectiveFlag) continue;
		if (!object[i].CanSeeFlag) continue;

		if (object[i].x <= Input::Mouse::MOUSE_WIN_X &&
			object[i].x + object[i].xSize >= Input::Mouse::MOUSE_WIN_X &&
			object[i].y <= Input::Mouse::MOUSE_WIN_Y &&
			object[i].y + object[i].ySize >= Input::Mouse::MOUSE_WIN_Y)
		{
			object[i].MouseFlag = TRUE;
			//if ((Input::Mouse::MOUSE_CLICK & MOUSE_INPUT_LEFT) != 0)
			if (Input::Mouse::MOUSE_LEFT == MOUSE_LEFT_PRESS_FIRST)
			{

				for (int j = 0;j < OBJECT_MAX;j++) {
					object[j].ActivationFlag = FALSE;

				}
				object[i].ActivationFlag = TRUE;
				latestClick = 1;

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
		if (!object[i].ExistenceFlag || !object[i].CanSeeFlag) continue;//ŽlŠp•`‰æ or ‘È‰~

		switch (object[i].ObjectType) {

		case OBJECT_TYPE::BUTTON:
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

			if (object[i].AnimationFlag) {

				if (object[i].MouseFlag && !object[i].ActivationFlag) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawBox(object[i].x + object[i].outsidePixel, object[i].y + object[i].outsidePixel, object[i].xSize + object[i].x - object[i].outsidePixel, object[i].ySize + object[i].y - object[i].outsidePixel, GetColor(0, 0, 0), TRUE);
				}
				else if (object[i].ActivationFlag) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
					DrawBox(object[i].x + object[i].outsidePixel, object[i].y + object[i].outsidePixel, object[i].xSize + object[i].x - object[i].outsidePixel, object[i].ySize + object[i].y - object[i].outsidePixel, GetColor(0, 0, 0), TRUE);
				}

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}

			break;

		case OBJECT_TYPE::PICTURE:

			if (object[i].WritingFlag) {
				DrawFormatStringToHandle(object[i].writingX, object[i].writingY, object[i].writingColor, object[i].FontHandle, object[i].writing.c_str());
			}

			DrawGraph(object[i].x + object[i].pictureX, object[i].y + object[i].pictureY, object[i].pictureNum, TRUE);

			break;

		case OBJECT_TYPE::PROGRESS:

			DrawBox(object[i].x, object[i].y, object[i].xSize + object[i].x, object[i].ySize + object[i].y, object[i].progressBackColor, TRUE);
			DrawBox(object[i].x, object[i].y, object[i].progressRange + object[i].x, object[i].ySize + object[i].y, object[i].progressForwardColor, TRUE);

			break;

		}
		
	}


}

