#include "TAB_OTHERS_Scene.hpp"
#include "AppData.h"
using namespace App;

TAB_OTHERS_Scene::TAB_OTHERS_Scene(ObjectManager &objectManager, Json& json, JsonManager& jsonManager)
	: SceneData(objectManager,json)
{
	/*jsonOthers[0] = { "NONE",
					"",
					"",
					"",
					"NONE" };
	int othersMax = 0;*/

	int othersMax = jsonManager.GetDataNum(SCENE::TAB_OTHERS);


	int a = 0;

	for (int i = 0;i < othersMax;i++, a++)
	{
		string name;

		name = "OTHERS" + to_string(i);

		int b = (int)i % 3;
		int a = (int)i / 3;

		jsonManager.GetData(SCENE::TAB_OTHERS, &jsonOthers[i], i);

		objectManager.Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		objectManager.ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		objectManager.WritingSet(name.c_str(), TRUE, jsonOthers[i].name);
		objectManager.WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);
		if (jsonOthers[i].picPath == "NONE") {
			objectManager.ImageChestSet(name.c_str(), TRUE, ".\\Content\\Pic\\NoPic.png");
		}
		else {
			objectManager.ImageChestSet(name.c_str(), TRUE, jsonOthers[i].picPath);
		}

		objectManager.ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	Ope::OTHERS_BUTTON_NUM = a;
}

void TAB_OTHERS_Scene::Update()
{
	for (int i = 0;i < Ope::OTHERS_BUTTON_NUM;i++)
	{
		string name;

		name = "OTHERS" + to_string(i);

		if (objectManager.GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			json = jsonOthers[i];
			Ope::JSON_MUSIC_FLAG = FALSE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
		}
	}
}

void TAB_OTHERS_Scene::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont("G50"), "Others");

	if (Ope::OTHERS_BUTTON_NUM == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), objectManager.GetHandleFont("G30"), "NotFound");
	}
}
