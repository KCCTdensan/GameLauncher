#include "SceneProcHome.h"
#include "AppData.h"
#include "PicPath.h"

using namespace App; // AppData.hのネームスペース排除
#pragma warning(push)
#pragma warning(disable:26495)

SceneProcHome::SceneProcHome(ObjectManager& objectManager, Json& json, JsonManager& jsonManager, SCENE scenes)
{
	PicPath picPath;
	jsonMan = &jsonManager;
	objMan = &objectManager;
	SceneNum = scenes;
	curJson = &json;

	objNum = jsonManager.GetDataNum(SceneNum);

	jsonData[0] = { "APP",
					"",
					"",
					"",
					picPath.tabApp };
	jsonData[1] = { "GAME",
					"",
					"",
					"",
					picPath.tabGame };
	jsonData[2] = { "3D MODEL",
					"",
					"",
					"",
					picPath.tabModel };
	jsonData[3] = { "MUSIC",
					"",
					"",
					"",
					picPath.tabMusic };
	jsonData[4] = { "VIDEO",
					"",
					"",
					"",
					picPath.tabVideo };
	jsonData[5] = { "OTHERS",
					"",
					"",
					"",
					picPath.tabOthers };
	int homeMax = 6;

	for (int i = 0; i < homeMax; i++) // ボタン設定をループ処理で必要分設定
	{
		string name;

		name = "HOME" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonData[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonData[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, picPath.noPic);
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonData[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
	}

	Ope::HOME_BUTTON_NUM = homeMax;
}

#pragma warning(pop)

void SceneProcHome::Update()
{
	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		string name;

		name = "HOME" + to_string(i);

		if ((*objMan).GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			Ope::SCENE_CHANGE_FLAG = TRUE;
			if (i == 0) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_APP;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
				{
					nameA = "APP" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 1) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_GAME;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
				{
					nameA = "GAME" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 2) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_3DMODEL;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
				{
					nameA = "MODE" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 3) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_MUSIC;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
				{
					nameA = "MUSIC" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 4) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_VIDEO;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
				{
					nameA = "VIDEO" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
			if (i == 5) {
				Ope::SCENE_CHANGE_NUM = SCENE::TAB_OTHERS;

				AllHide();

				string nameA;

				for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
				{
					nameA = "OTHERS" + to_string(i);

					(*objMan).ChangeVarBool(nameA.c_str(), VAR::CAN_SEE_FLAG, TRUE);
				}

			}
		}
	}
	// 選ばれた番号を取得してそれに伴った表示をさせる
}

void SceneProcHome::AllHide()
{
	string name;

	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		name = "HOME" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
	{
		name = "APP" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		name = "GAME" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
	{
		name = "MODE" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
	{
		name = "MUSIC" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
	{
		name = "VIDEO" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
	{
		name = "OTHERS" + to_string(i);

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	return;
}