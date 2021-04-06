#include "TAB_MUSIC_Scene.hpp"
#include "AppData.h"
#include "PicPath.h"
using namespace App;

TAB_MUSIC_Scene::TAB_MUSIC_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager,json)
{
	PicPath picPath;
	jsonMan = &jsonManager;

	int musicMax = jsonManager.GetDataNum(SCENE::TAB_MUSIC);

	int a = 0;

	for (int i = 0;i < musicMax;i++, a++)
	{
		string name;

		name = "MUSIC" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		jsonManager.GetData(SCENE::TAB_MUSIC, &jsonMusic[i], i);

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonMusic[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonMusic[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, picPath.noPic);
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonMusic[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::MUSIC_BUTTON_NUM = a;

	if ((Ope::MUSIC_BUTTON_NUM / 3 * 350) + 300 + 150 <= App::BACKGROUND_SIZE_Y)
	{
		canScroll = FALSE;
	}
	else {
		canScroll = TRUE;
	}
}

void TAB_MUSIC_Scene::Update()
{
	for (int i = 0;i < Ope::MUSIC_BUTTON_NUM;i++)
	{
		string name;

		name = "MUSIC" + to_string(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonMusic[i];
			Ope::JSON_MUSIC_FLAG = TRUE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}

	if (canScroll) {

		int tempPos = 0;
		scrollCurrentPosBefore = scrollCurrentPos;

		switch (Input::Scroll::SCHOOL_SIZE)
		{
		case -1:
			tempPos -= App::SCROLL_SIZE;
			break;
		case 1:
			tempPos += App::SCROLL_SIZE;
			break;
		default:
			break;
		}
		if (scrollCurrentPos + tempPos < -1 * ((int)(Ope::MUSIC_BUTTON_NUM / 3) * 350))//â∫Ç‹Ç≈çsÇ¡ÇΩÇ©ÇîªíË
		{
			scrollCurrentPos = -1 * ((Ope::MUSIC_BUTTON_NUM / 3) * 350);

			MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
		}
		else if (scrollCurrentPos + tempPos > 0)//è„Ç‹Ç≈çsÇ¡ÇΩÇ©ÇîªíË
		{
			scrollCurrentPos = 0;

			MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
		}
		else {
			scrollCurrentPos += tempPos;
			MoveObj(tempPos);
		}
	}
}

void TAB_MUSIC_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50 + scrollCurrentPos, GetColor(255, 255, 255), objectManager.GetHandleFont("G50"), "Music");

	if (Ope::MUSIC_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont("G30"), "NotFound");
	}
}

void TAB_MUSIC_Scene::MoveObj(int size)
{
	int a = 0;

	for (int i = 0; i < jsonMan->GetDataNum(SCENE::TAB_GAME); i++, a++)
	{
		string name;

		name = "GAME" + to_string(i);

		int objY = objectManager.GetVarInt(name.c_str(), VAR::Y);

		objectManager.ChangeVarInt(name.c_str(), VAR::Y, objY + size);
	}
}
