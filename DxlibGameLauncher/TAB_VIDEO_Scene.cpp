#include "TAB_VIDEO_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_VIDEO_Scene::TAB_VIDEO_Scene(ObjectManager &objectManager, Json& json)
	: SceneData(objectManager,json)
{
	jsonVideo[0] = { L"NONE",
					L".\\Content\\Software\\VIDEO\\FNBR_AudioSynBars_041719.mp4",
					L"",
					L"",
					L"NONE" };
	int videoMax = 0;

	int a = 0;

	for (int i = 0;i < videoMax;i++, a++)
	{
		wstring name;

		name = L"VIDEO" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonVideo[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonVideo[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonVideo[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::VIDEO_BUTTON_NUM = a;
}

void TAB_VIDEO_Scene::Update()
{
	for (int i = 0;i < Ope::VIDEO_BUTTON_NUM;i++)
	{
		wstring name;

		name = L"VIDEO" + to_wstring(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonVideo[i];
			Ope::JSON_MUSIC_FLAG = FALSE;
			Ope::JSON_VIDEO_FLAG = TRUE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}
}

void TAB_VIDEO_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Video");

	if (Ope::VIDEO_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G30"), L"NotFound");
	}
}
