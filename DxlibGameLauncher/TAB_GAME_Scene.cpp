#include "TAB_GAME_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_GAME_Scene::TAB_GAME_Scene(ObjectManager& objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager,json)
{

	/*jsonGame[0] = { "Minesweeper",
					".\\Content\\Software\\GAME\\Minesweeper\\Mine.bat",
					"1.00",
					"�����P�N���̎��ɍ������i�ł��B\n2�̃��[�h������̂Ŋy����ł��������I",
					".\\Content\\Pic\\MineSweeper.png" };
	jsonGame[1] = { "Starbox",
					".\\Content\\Software\\GAME\\starbox\\starboxlauncherc.exe",
					"1.60",
					"�������Ƃ����e�����[�I",
					".\\Content\\Pic\\starbox.png" };
	jsonGame[2] = { "�e��YOKE",
					".\\Content\\Software\\GAME\\�e��YOKE\\�e��yoke.exe",
					"1.0.12",
					"�{�C�Œe�����y���݂����l��\nHSP�R���e�X�g�ɂ���o",
					".\\Content\\Pic\\iconC.png" };
	jsonGame[3] = { "S.T.G",
					".\\Content\\Software\\GAME\\STG\\stg.exe",
					"1.6.0",
					"���[�U�[����ь����V���[�e�B���O!",
					".\\Content\\Pic\\STG.png" };
	jsonGame[4] = { "PanalPuzzule",
					".\\Content\\Software\\GAME\\PanelPuzzule\\�p�l���Q�[��.exe",
					"1.0.0",
					"�p�l�����Ђ�����Ԃ��Ď�{�ʂ�̖͗l�ɂ���Q�[���ł��I\n���\����̂Ŋ撣���ĉ����Ă݂Ă��������I",
					"NONE" };
	jsonGame[5] = { "PUBG",
					".\\Content\\Software\\GAME\\PUBG\\PUBG.exe",
					"1.0.0",
					"P U B G",
					"NONE" };
	int gameMax = 6;*/

	int gameMax = jsonManager.GetDataNum(SCENE::TAB_GAME);

	int a = 0;

	for (int i = 0;i < gameMax;i++,a++)
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
	for (int i = 0;i < Ope::GAME_BUTTON_NUM;i++)
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
