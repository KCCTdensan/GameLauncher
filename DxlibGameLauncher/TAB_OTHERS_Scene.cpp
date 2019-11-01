#include "TAB_OTHERS_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_OTHERS_Scene::TAB_OTHERS_Scene(ObjectManager &objectManager, Json& json)
	: SceneData(objectManager,json)
{
	jsonOthers[0] = { L"NONE",
					L"",
					L"",
					L"",
					L"NONE" };
	int othersMax = 0;

	int a = 0;

	for (int i = 0;i < othersMax;i++, a++)
	{
		wstring name;

		name = L"OTHERS" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonOthers[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonOthers[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonOthers[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::OTHERS_BUTTON_NUM = a;
}

void TAB_OTHERS_Scene::Update()
{
}

void TAB_OTHERS_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Others");
}
