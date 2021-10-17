#include "SceneProc.h"
#include "AppData.h"
#include "PicPath.h"
#include "InputManager.h"
using namespace App;
#pragma warning(push)
#pragma warning(disable:26495)

SceneProc::SceneProc()
{
}
#pragma warning(pop)

SceneProc::SceneProc(ObjectManager& objectManager, Json& json, JsonManager& jsonManager, SCENE scenes)
{
	PicPath picPath;
	jsonMan = &jsonManager;
	objMan = &objectManager;
	SceneNum = scenes;
	curJson = &json;

	objNum = jsonManager.GetDataNum(scenes);
	
	for (int i = 0; i < objNum; i++)
	{
		string name;

		switch (SceneNum) {
		case SCENE::TAB_APP:
			name = "APP" + to_string(i); break;
		case SCENE::TAB_GAME:
			name = "GAME" + to_string(i); break;
		case SCENE::TAB_MUSIC:
			name = "MUSIC" + to_string(i); break;
		case SCENE::TAB_3DMODEL:
			name = "MDOEL" + to_string(i); break;
		case SCENE::TAB_VIDEO:
			name = "VIDEO" + to_string(i); break;
		case SCENE::TAB_OTHERS:
			name = "OTHERS" + to_string(i); break;
		}

		int b = (int)i % 3;
		int a = (int)i / 3;

		jsonManager.GetData(SceneNum, &jsonData[i], i); // jsonDataÇscenesÇ…ÇÊÇËä«óùéÊìæ

		(*objMan).Set(name.c_str(), 450 + (b * 300), 150 + (a * 350), 250, 300, OBJECT_TYPE::BUTTON);
		(*objMan).ColorSet(name.c_str(), FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
		(*objMan).WritingSet(name.c_str(), TRUE, jsonData[i].name);
		(*objMan).WritingFontSetToHandle(name.c_str(), "G30", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_BOTTOM);


		if (jsonData[i].picPath == "NONE") {
			(*objMan).ImageChestSet(name.c_str(), TRUE, picPath.noPic);
		}
		else {
			(*objMan).ImageChestSet(name.c_str(), TRUE, jsonData[i].picPath);
		}

		(*objMan).ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE); // Home ìÆÇ©Ç∑
	}

	switch (SceneNum) {
	case SCENE::TAB_APP:
		Ope::APP_BUTTON_NUM = objNum; break;
	case SCENE::TAB_GAME:
		Ope::GAME_BUTTON_NUM = objNum; break;
	case SCENE::TAB_MUSIC:
		Ope::MUSIC_BUTTON_NUM = objNum; break;
	case SCENE::TAB_3DMODEL:
		Ope::MODEL_BUTTON_NUM = objNum; break;
	case SCENE::TAB_VIDEO:
		Ope::VIDEO_BUTTON_NUM = objNum; break;
	case SCENE::TAB_OTHERS:
		Ope::OTHERS_BUTTON_NUM = objNum; break;
	}

	if ((objNum / 3 * 350) + 300 + 150 <= App::BACKGROUND_SIZE_Y)
	{
		canScroll = FALSE;
	}
	else {
		canScroll = TRUE;
	}
}

void SceneProc::Update()
{
	for (int i = 0; i < objNum; i++)
	{
		string name;

		switch (SceneNum) {
		case SCENE::TAB_APP:
			name = "APP" + to_string(i); break;
		case SCENE::TAB_GAME:
			name = "GAME" + to_string(i); break;
		case SCENE::TAB_MUSIC:
			name = "MUSIC" + to_string(i); break;
		case SCENE::TAB_3DMODEL:
			name = "MDOEL" + to_string(i); break;
		case SCENE::TAB_VIDEO:
			name = "VIDEO" + to_string(i); break;
		case SCENE::TAB_OTHERS:
			name = "OTHERS" + to_string(i); break;
		}

		if ((*objMan).GetVarBool(name.c_str(), VAR::ACTIVATION_FLAG))
		{
			*curJson = jsonData[i];
			Ope::JSON_MUSIC_FLAG = FALSE;
			Ope::JSON_VIDEO_FLAG = FALSE;
			Ope::JSON_PICTURE_FLAG = FALSE;
			string name;


			switch (SceneNum) {
			case SCENE::TAB_APP:
				break;
			case SCENE::TAB_GAME:
				break;
			case SCENE::TAB_MUSIC:
				Ope::JSON_MUSIC_FLAG = TRUE; break;
			case SCENE::TAB_3DMODEL:
				break;
			case SCENE::TAB_VIDEO:
				Ope::JSON_VIDEO_FLAG = TRUE; break;
			case SCENE::TAB_OTHERS:
				Ope::JSON_PICTURE_FLAG = TRUE;
				break;
			}
		}
	}

	if (canScroll) {

		int tempPos = 0;
		scrollCurrentPosBefore = scrollCurrentPos;

		switch (Input::Scroll::SCHOOL_SIZE)
		{
		case -1:
			tempPos -= App::SCROLL_SIZE;
			break;
		case 1:
			tempPos += App::SCROLL_SIZE;
			break;
		default:
			break;
		}
		if (scrollCurrentPos + tempPos < -1 * ((int)(objNum / 3) * 350))//â∫Ç‹Ç≈çsÇ¡ÇΩÇ©ÇîªíË
		{
			scrollCurrentPos = -1 * ((objNum / 3) * 350);

			MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
		}
		else if (scrollCurrentPos + tempPos > 0)//è„Ç‹Ç≈çsÇ¡ÇΩÇ©ÇîªíË
		{
			scrollCurrentPos = 0;

			MoveObj(scrollCurrentPosBefore - scrollCurrentPos);
		}
		else {
			scrollCurrentPos += tempPos;
			MoveObj(tempPos);
		}

		float rate = -1.0f * (float)scrollCurrentPos / (((float)objNum / 3.0f) * 350.0f);
	}
}

void SceneProc::Draw()
{
	DrawBox(0, 0, App::BACKGROUND_SIZE_X, App::BACKGROUND_SIZE_Y, GetColor(BLACK, BLACK, BLACK), TRUE);

	string name;

	switch (SceneNum) {
	case SCENE::TAB_HOME:
		name = "HOME"; break;
	case SCENE::TAB_APP:
		name = "APP"; break;
	case SCENE::TAB_GAME:
		name = "GAME"; break;
	case SCENE::TAB_MUSIC:
		name = "MUSIC"; break;
	case SCENE::TAB_3DMODEL:
		name = "MDOEL"; break;
	case SCENE::TAB_VIDEO:
		name = "VIDEO"; break;
	case SCENE::TAB_OTHERS:
		name = "OTHERS"; break;
	}

	DrawFormatStringToHandle(410, 50 + scrollCurrentPos, GetColor(255, 255, 255),(*objMan).GetHandleFont("G50"), name.c_str());

	if (objNum == 0)
	{
		DrawFormatStringToHandle(410, 150, GetColor(255, 255, 255), (*objMan).GetHandleFont("G30"), "NotFound");
	}
}

void SceneProc::MoveObj(int size)
{
	int a = 0;

	for (int i = 0; i < jsonMan->GetDataNum(SceneNum); i++, a++)
	{
		string name;

		switch (SceneNum) {
		case SCENE::TAB_APP:
			name = "APP" + to_string(i); break;
		case SCENE::TAB_GAME:
			name = "GAME" + to_string(i); break;
		case SCENE::TAB_MUSIC:
			name = "MUSIC" + to_string(i); break;
		case SCENE::TAB_3DMODEL:
			name = "MDOEL" + to_string(i); break;
		case SCENE::TAB_VIDEO:
			name = "VIDEO" + to_string(i); break;
		case SCENE::TAB_OTHERS:
			name = "OTHERS" + to_string(i); break;
		}

		int objY = (*objMan).GetVarInt(name.c_str(), VAR::Y);

		(*objMan).ChangeVarInt(name.c_str(), VAR::Y, objY + size);
	}
}
