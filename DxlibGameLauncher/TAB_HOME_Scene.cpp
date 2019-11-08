#include "TAB_HOME_Scene.hpp"
#include "AppData.h"

using namespace App; // AppData.hのネームスペース排除

TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager& objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager, json)
{

	jsonHome[0] = { "APP",
					"",
					"",
					"",
					".\\Content\\Pic\\AppTabIcon.png" };
	jsonHome[1] = { "GAME",
					"",
					"",
					"",
					".\\Content\\Pic\\GameTabIcon.png" };
	jsonHome[2] = { "3D MODE",
					"",
					"",
					"",
					".\\Content\\Pic\\ModelTabIcon.png" };
	jsonHome[3] = { "MUSIC",
					"",
					"",
					"",
					".\\Content\\Pic\\kcctjacketomote.png" };
	jsonHome[4] = { "VIDEO",
					"",
					"",
					"",
					".\\Content\\Pic\\VideoTabIcon.png" };
	jsonHome[5] = { "OTHERS",
					"",
					"",
					"",
					".\\Content\\Pic\\OthersTabIcon.png" };
	int homeMax = 6;

	int a = 0;

	for (int i = 0;i < homeMax;i++, a++) // ボタン設定をループ処理で必要分設定
	{
		string name;

		name = "HOME" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonHome[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonHome[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, ".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonHome[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
	}

	Ope::HOME_BUTTON_NUM = a;
}

void TAB_HOME_Scene::Update()
{
	for (int i = 0;i < Ope::HOME_BUTTON_NUM;i++)
	{
		string name;

		name = "HOME" + to_string(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			Ope::SCENE_CHANGE_FLAG = TRUE;
			if (i == 0) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_APP;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
				{
					nameA = "APP" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 1) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_GAME;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
				{
					nameA = "GAME" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 2) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_3DMODEL;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
				{
					nameA = "MODE" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 3) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_MUSIC;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
				{
					nameA = "MUSIC" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 4) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_VIDEO;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
				{
					nameA = "VIDEO" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 5) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_OTHERS;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
				{
					nameA = "OTHERS" + to_string(i);

					objectManager.ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
		}
	}
	// 選ばれた番号を取得してそれに伴った表示をさせる
}

void TAB_HOME_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont("G50"), "Home");
	

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "x: %d", Input::Mouse::MOUSE_WIN_X);
}

void TAB_HOME_Scene::AllHide()
{
	string name;

	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		name = "HOME" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
	{
		name = "APP" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		name = "GAME" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
	{
		name = "MODE" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
	{
		name = "MUSIC" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
	{
		name = "VIDEO" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
	{
		name = "OTHERS" + to_string(i);

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	return;
}