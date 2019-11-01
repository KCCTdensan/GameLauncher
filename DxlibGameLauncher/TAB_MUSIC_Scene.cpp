#include "TAB_MUSIC_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_MUSIC_Scene::TAB_MUSIC_Scene(ObjectManager &objectManager, Json& json)
	: SceneData(objectManager,json)
{
	jsonMusic[0] = { L"Halloween\nparty-nightmare",
					L".\\Content\\Software\\MUSIC\\01-Towa-_-kumataro-_-P.K.A-Halloween-party-nightmare.mp3",
					L"1.00",
					L"高専祭音楽CDにも入っています！",
					L".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[1] = { L"そこら辺の雑魚戦",
					L".\\Content\\Software\\MUSIC\\02-Shadow-K-HERO-_そこら辺の雑魚戦_.mp3",
					L"1.00",
					L"高専祭音楽CDにも入っています！",
					L".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[2] = { L"Big-Wave",
					L".\\Content\\Software\\MUSIC\\03-kumataro-Big-Wave.mp3",
					L"1.00",
					L"高専祭音楽CDにも入っています！",
					L".\\Content\\Pic\\iconA.png" };
	jsonMusic[3] = { L"Save-The-Dayz",
					L".\\Content\\Software\\MUSIC\\04-Towa-Save-The-Dayz.mp3",
					L"1.00",
					L"高専祭音楽CDにも入っています！",
					L".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[4] = { L"Color",
					L".\\Content\\Software\\MUSIC\\05-kumataro-Color.mp3",
					L"1.00",
					L"高専祭音楽CDにも入っています！",
					L".\\Content\\Pic\\iconB.png" };
	jsonMusic[5] = { L"Cosmic World",
					L".\\Content\\Software\\MUSIC\\Cosmic World.mp3",
					L"1.00",
					L"テクノポップみたいな曲です！",
					L".\\Content\\Pic\\kumataro.png" };
	int musicMax = 6;

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
	for (int i = 0;i < Ope::MUSIC_BUTTON_NUM;i++)
	{
		wstring name;

		name = L"MUSIC" + to_wstring(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonMusic[i];
			Ope::JSON_MUSIC_FLAG = TRUE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}
}

void TAB_MUSIC_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Music");
}
