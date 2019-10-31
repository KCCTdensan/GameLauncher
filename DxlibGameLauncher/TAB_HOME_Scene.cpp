#include "TAB_HOME_Scene.hpp"
#include "AppData.h"

using namespace App;

TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager& objectManager)
	: SceneData(objectManager)
{
	jsonGame[0] = { L"Minesweeper",
					L".\\Content\\Software\\GAME\\Minesweeper\\Minesweeper.exe",
					L"1.00",
					L"Minesweeperのゲーム" };
	jsonGame[1] = { L"Starbox",
					L".\\Content\\Software\\GAME\\starbox\\starboxlauncherc.exe",
					L"1.60",
					L"ゆっくりとした弾幕げー！" };
	jsonGame[2] = { L"弾幕YOKE",
					L".\\Content\\Software\\GAME\\弾幕YOKE\\弾幕yoke.exe",
					L"1.0.12",
					L"本気で弾幕を楽しみたい人へ"};
	jsonGame[3] = { L"S.T.G",
					L".\\Content\\Software\\GAME\\STG\\stg.exe",
					L"1.6.0",
					L"レーザーが飛び交うシューティング!" };

	//manager = &objectManager;

	/*

	objectManager.Set(L"test", 100, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"test", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"test", TRUE, L"DEBUG");
	objectManager.WritingFontSet(L"test", OBJECT_FONT_GOTHIC, 30, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);
	objectManager.ImageChestSet(L"test", TRUE, L"D:\\Users\\seiya\\Desktop\\無題.png", 0, 0);

	このようにボタン，ピクチャーを作る

	*/

	int a = 0;

	for (int i = 0;i < 1;i++)
	{
		wstring name;

		name = L"HOME" + to_wstring(i);

		objectManager.Set(name.c_str(), 400, 150, 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
		objectManager.WritingSet(name.c_str(), TRUE, L"TEST");
		objectManager.WritingFontSetToHandle(name.c_str(), L"G50", GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);

		a++;
	}

	Ope::HOME_BUTTON_NUM = a;

	//wstring a;

	//a = L"aaa" + to_wstring(7); 例
}

void TAB_HOME_Scene::Update()
{
	
	// 選ばれた番号を取得してそれに伴った表示をさせる
}

void TAB_HOME_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Home");

	//DrawFormatString(0, 0, GetColor(255, 255, 255), L"x: %d", Input::Mouse::MOUSE_WIN_X);
}
