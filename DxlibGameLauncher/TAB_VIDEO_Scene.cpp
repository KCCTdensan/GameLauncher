#include "TAB_VIDEO_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_VIDEO_Scene::TAB_VIDEO_Scene(ObjectManager &objectManager, Json& json)
	: SceneData(objectManager,json)
{
	jsonVideo[0] = { L"NONE",
					L"",
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
}

void TAB_VIDEO_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Video");
}
