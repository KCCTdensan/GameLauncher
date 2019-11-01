#include "TAB_GAME_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_GAME_Scene::TAB_GAME_Scene(ObjectManager& objectManager, Json& json)
	: SceneData(objectManager,json)
{

	jsonGame[0] = { L"Minesweeper",
					L".\\Content\\Software\\GAME\\Minesweeper\\Mine.bat",
					L"1.00",
					L"�����P�N���̎��ɍ������i�ł��B\n2�̃��[�h������̂Ŋy����ł��������I",
					L".\\Content\\Pic\\MineSweeper.png" };
	jsonGame[1] = { L"Starbox",
					L".\\Content\\Software\\GAME\\starbox\\starboxlauncherc.exe",
					L"1.60",
					L"�������Ƃ����e�����[�I",
					L".\\Content\\Pic\\starbox.png" };
	jsonGame[2] = { L"�e��YOKE",
					L".\\Content\\Software\\GAME\\�e��YOKE\\�e��yoke.exe",
					L"1.0.12",
					L"�{�C�Œe�����y���݂����l��\nHSP�R���e�X�g�ɂ���o",
					L".\\Content\\Pic\\iconC.png" };
	jsonGame[3] = { L"S.T.G",
					L".\\Content\\Software\\GAME\\STG\\stg.exe",
					L"1.6.0",
					L"���[�U�[����ь����V���[�e�B���O!",
					L".\\Content\\Pic\\STG.png" };
	jsonGame[4] = { L"PanalPuzzule",
					L".\\Content\\Software\\GAME\\PanelPuzzule\\�p�l���Q�[��.exe",
					L"1.0.0",
					L"�p�l�����Ђ�����Ԃ��Ď�{�ʂ�̖͗l�ɂ���Q�[���ł��I\n���\����̂Ŋ撣���ĉ����Ă݂Ă��������I",
					L"NONE" };
	jsonGame[5] = { L"PUBG",
					L".\\Content\\Software\\GAME\\PUBG\\PUBG.exe",
					L"1.0.0",
					L"P U B G",
					L"NONE" };
	int gameMax = 6;

	int a = 0;

	for (int i = 0;i < gameMax;i++,a++)
	{
		wstring name;

		name = L"GAME" + to_wstring(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonGame[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), L"G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonGame[i].picPath == L"NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, L".\\Content\\Pic\\NoPic.png");
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
		wstring name;

		name = L"GAME" + to_wstring(i);

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

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Game");

	if (Ope::GAME_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G30"), L"NotFound");
	}

}
