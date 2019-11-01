#include "TAB_3DMODEL_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_3DMODEL_Scene::TAB_3DMODEL_Scene(ObjectManager &objectManager, Json& json)
	: SceneData(objectManager,json)
{
	jsonModel[0] = { L"NONE",
					L"",
					L"",
					L"",
					L"NONE" };
	int modelMax = 0;

	int a = 0;

	for (int i = 0;i < modelMax;i++, a++)
	{
		wstring name;

		name = L"MODEL" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonModel[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonModel[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonModel[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::MODEL_BUTTON_NUM = a;
}

void TAB_3DMODEL_Scene::Update()
{
	for (int i = 0;i < Ope::MODEL_BUTTON_NUM;i++)
	{
		wstring name;

		name = L"MODEL" + to_wstring(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonModel[i];
			Ope::JSON_MUSIC_FLAG = FALSE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}
}

void TAB_3DMODEL_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"3D Model");

	if (Ope::MODEL_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G30"), L"NotFound");
	}
}
