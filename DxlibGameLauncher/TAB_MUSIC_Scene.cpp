#include "TAB_MUSIC_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_MUSIC_Scene::TAB_MUSIC_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{
	jsonMusic[0] = { L"NONE",
					L"",
					L"",
					L"",
					L"NONE" };
	int musicMax = 0;

	int a = 0;

	for (int i = 0;i < musicMax;i++, a++)
	{
		wstring name;

		name = L"MUSIC" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonMusic[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonMusic[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonMusic[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::MUSIC_BUTTON_NUM = a;
}

void TAB_MUSIC_Scene::Update()
{
}

void TAB_MUSIC_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Music");
}
