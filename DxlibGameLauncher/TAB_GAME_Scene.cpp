#include "TAB_GAME_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_GAME_Scene::TAB_GAME_Scene(ObjectManager& objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager, json)
{
	jsonMan = &jsonManager;

	int gameMax = jsonManager.GetDataNum(SCENE::TAB_GAME);

	int a = 0;

	for (int i = 0; i < gameMax; i++, a++)
	{
		string name;

		name = "GAME" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		jsonManager.GetData(SCENE::TAB_GAME, &jsonGame[i], i);

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonGame[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonGame[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, ".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonGame[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::GAME_BUTTON_NUM = a;

}

void TAB_GAME_Scene::Update()
{
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		string name;

		name = "GAME" + to_string(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonGame[i];
			Ope::JSON_MUSIC_FLAG = FALSE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}

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
	if (scrollCurrentPos + tempPos < -1 * ((int)(Ope::GAME_BUTTON_NUM / 3) * 350))//下まで行ったかを判定
	{
		scrollCurrentPos = -1 * ((Ope::GAME_BUTTON_NUM / 3) * 350);

		MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
	}
	else if (scrollCurrentPos + tempPos > 0)//上まで行ったかを判定
	{
		scrollCurrentPos = 0;

		MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
	}
	else {
		scrollCurrentPos += tempPos;
		MoveObj(tempPos);
	}
}

void TAB_GAME_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont("G50"), "Game");

	if (Ope::GAME_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont("G30"), "NotFound");
	}

}

void TAB_GAME_Scene::MoveObj(int size)
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
