#include "TAB_HOME_Scene.hpp"
#include "AppData.h"

using namespace App;

TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager& objectManager, Json& json)
	: SceneData(objectManager, json)
{

	jsonHome[0] = { L"APP",
					L"",
					L"",
					L"",
					L".\\Content\\Pic\\AppTabIcon.png" };
	jsonHome[1] = { L"GAME",
					L"",
					L"",
					L"",
					L".\\Content\\Pic\\GameTabIcon.png" };
	jsonHome[2] = { L"3D MODEL",
					L"",
					L"",
					L"",
					L".\\Content\\Pic\\ModelTabIcon.png" };
	jsonHome[3] = { L"MUSIC",
					L"",
					L"",
					L"",
					L"NONE" };
	jsonHome[4] = { L"VIDEO",
					L"",
					L"",
					L"",
					L".\\Content\\Pic\\VideoTabIcon.png" };
	jsonHome[5] = { L"OTHERS",
					L"",
					L"",
					L"",
					L".\\Content\\Pic\\OthersTabIcon.png" };
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
	for (int i = 0;i < Ope::HOME_BUTTON_NUM;i++)
	{
		wstring name;

		name = L"HOME" + to_wstring(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			Ope::SCENE_CHANGE_FLAG = TRUE;
			if (i == 0) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_APP;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
				{
					nameA = L"APP" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 1) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_GAME;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
				{
					nameA = L"GAME" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 2) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_3DMODEL;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
				{
					nameA = L"MODEL" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 3) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_MUSIC;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
				{
					nameA = L"MUSIC" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 4) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_VIDEO;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
				{
					nameA = L"VIDEO" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 5) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_OTHERS;

				AllHide();

				wstring nameA;

				for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
				{
					nameA = L"OTHERS" + to_wstring(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
		}
	}
	// ‘I‚Î‚ê‚½”Ô†‚ðŽæ“¾‚µ‚Ä‚»‚ê‚É”º‚Á‚½•\Ž¦‚ð‚³‚¹‚é
}

void TAB_HOME_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Home");

	//DrawFormatString(0, 0, GetColor(255, 255, 255), L"x: %d", Input::Mouse::MOUSE_WIN_X);
}

void TAB_HOME_Scene::AllHide()
{
	wstring name;

	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		name = L"HOME" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
	{
		name = L"APP" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		name = L"GAME" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
	{
		name = L"MODEL" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
	{
		name = L"MUSIC" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
	{
		name = L"VIDEO" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
	{
		name = L"OTHERS" + to_wstring(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	return;
}