#include "TAB_MUSIC_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_MUSIC_Scene::TAB_MUSIC_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager,json)
{
	/*jsonMusic[0] = { "Halloween\nparty-nightmare",
					".\\Content\\Software\\MUSIC\\01-Towa-_-kumataro-_-P.K.A-Halloween-party-nightmare.mp3",
					"1.00",
					"高専祭音楽CDにも入っています！",
					".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[1] = { "そこら辺の雑魚戦",
					".\\Content\\Software\\MUSIC\\02-Shadow-K-HERO-_そこら辺の雑魚戦_.mp3",
					"1.00",
					"高専祭音楽CDにも入っています！",
					".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[2] = { "Big-Wave",
					".\\Content\\Software\\MUSIC\\03-kumataro-Big-Wave.mp3",
					"1.00",
					"高専祭音楽CDにも入っています！",
					".\\Content\\Pic\\iconA.png" };
	jsonMusic[3] = { "Save-The-Dayz",
					".\\Content\\Software\\MUSIC\\04-Towa-Save-The-Dayz.mp3",
					"1.00",
					"高専祭音楽CDにも入っています！",
					".\\Content\\Pic\\kcctjacketomote.png" };
	jsonMusic[4] = { "Color",
					".\\Content\\Software\\MUSIC\\05-kumataro-Color.mp3",
					"1.00",
					"高専祭音楽CDにも入っています！",
					".\\Content\\Pic\\iconB.png" };
	jsonMusic[5] = { "Cosmic World",
					".\\Content\\Software\\MUSIC\\Cosmic World.mp3",
					"1.00",
					"テクノポップみたいな曲です！",
					".\\Content\\Pic\\kumataro.png" };
	int musicMax = 6;*/

	int musicMax = jsonManager.GetDataNum(SCENE::TAB_MUSIC);

	int a = 0;

	for (int i = 0;i < musicMax;i++, a++)
	{
		string name;

		name = "MUSIC" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		jsonManager.GetData(SCENE::TAB_MUSIC, &jsonMusic[i], i);

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonMusic[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonMusic[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, ".\\Content\\Pic\\NoPic.png");
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
		string name;

		name = "MUSIC" + to_string(i);

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

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont("G50"), "Music");

	if (Ope::MUSIC_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont("G30"), "NotFound");
	}
}
