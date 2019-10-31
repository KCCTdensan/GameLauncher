#include "TAB_GAME_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_GAME_Scene::TAB_GAME_Scene(ObjectManager& objectManager)
	: SceneData(objectManager)
{

	jsonGame[0] = { L"Minesweeper",
					L".\\Content\\Software\\GAME\\Minesweeper\\Minesweeper.exe",
					L"1.00",
					L"Minesweeperのゲーム",
					L"NONE" };
	jsonGame[1] = { L"Starbox",
					L".\\Content\\Software\\GAME\\starbox\\starboxlauncherc.exe",
					L"1.60",
					L"ゆっくりとした弾幕げー！",
					L"NONE" };
	jsonGame[2] = { L"弾幕YOKE",
					L".\\Content\\Software\\GAME\\弾幕YOKE\\弾幕yoke.exe",
					L"1.0.12",
					L"本気で弾幕を楽しみたい人へ",
					L"NONE" };
	jsonGame[3] = { L"S.T.G",
					L".\\Content\\Software\\GAME\\STG\\stg.exe",
					L"1.6.0",
					L"レーザーが飛び交うシューティング!",
					L"NONE" };
	int gameMax = 4;

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
}

void TAB_GAME_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Game");

}
