#include "TAB_HOME_Scene.hpp"
#include "AppData.h"

using namespace App;

TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager& objectManager)
	: SceneData(objectManager)
{

	jsonHome[0] = { L"APP",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[1] = { L"GAME",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[2] = { L"3D MODEL",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[3] = { L"MUSIC",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[4] = { L"VIDEO",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[5] = { L"OTHERS",
					L"",
					L"",
					L"",
					L"NONE" };
	int homeMax = 6;

	int a = 0;

	for (int i = 0;i < homeMax;i++, a++)
	{
		wstring name;

		name = L"HOME" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonHome[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonHome[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonHome[i].picPath);
		}

		//objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::HOME_BUTTON_NUM = a;
}

void TAB_HOME_Scene::Update()
{

	// ‘I‚Î‚ê‚½”Ô†‚ðŽæ“¾‚µ‚Ä‚»‚ê‚É”º‚Á‚½•\Ž¦‚ð‚³‚¹‚é
}

void TAB_HOME_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Home");

	//DrawFormatString(0, 0, GetColor(255, 255, 255), L"x: %d", Input::Mouse::MOUSE_WIN_X);
}
