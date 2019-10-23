#include "HEADER_Scene.h"

HEADER_Scene::HEADER_Scene(ObjectManager& objectManager, MusicManager& musicManager)
{
	objectManager.Set(L"HHSB", 50, 350, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HHSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HHSB", TRUE, L"Home");
	objectManager.WritingFontSetToHandle(L"HHSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HASB", 50, 450, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HASB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HASB", TRUE, L"App");
	objectManager.WritingFontSetToHandle(L"HASB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HGSB", 50, 550, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HGSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HGSB", TRUE, L"Game");
	objectManager.WritingFontSetToHandle(L"HGSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"H3SB", 50, 650, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"H3SB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"H3SB", TRUE, L"3D Model");
	objectManager.WritingFontSetToHandle(L"H3SB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HMSB", 50, 750, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HMSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HMSB", TRUE, L"Music");
	objectManager.WritingFontSetToHandle(L"HMSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HVSB", 50, 850, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HVSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HVSB", TRUE, L"Video");
	objectManager.WritingFontSetToHandle(L"HVSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HOSB", 50, 950, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HOSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HOSB", TRUE, L"Others");
	objectManager.WritingFontSetToHandle(L"HOSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HPicKCCT", 50, 50, 250, 250, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HPicKCCT", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.ImageChestSet(L"HPicKCCT", TRUE, L".\\pic\\KCCTicon.png", 0, 0);
	objectManager.ChangeVarBool(L"HPicKCCT", VAR::ANIMATION_FLAG, FALSE);

	objectManager.Set(L"HOSB", 50, 950, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet(L"HOSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HOSB", TRUE, L"Others");
	objectManager.WritingFontSetToHandle(L"HOSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"Launch", 1450, 880, 420, 150, OBJECT_TYPE::BUTTON);
	//objectManager.ColorSet(L"Launch", FALSE, NULL, NULL, TRUE, GetColor(63, 72, 204));
	objectManager.ColorSet(L"Launch", TRUE, GetColor(255,190,0), 3, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"Launch", TRUE, L"Launch");
	objectManager.WritingFontSetToHandle(L"Launch", L"G50", GetColor(255,255,255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);




	this->objectManager = &objectManager;
	this->musicManager = &musicManager;

}

void HEADER_Scene::Update()
{
	if (objectManager->GetVarBool(L"HPicKCCT", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_HOME;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
		{
			name = L"HOME" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HPicKCCT", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HHSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_HOME;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
		{
			name = L"HOME" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HHSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HASB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_APP;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
		{
			name = L"APP" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HASB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HGSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_GAME;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
		{
			name = L"GAME" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HGSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"H3SB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_3DMODEL;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
		{
			name = L"MODEL" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"H3SB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HMSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_MUSIC;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
		{
			name = L"MUSIC" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HMSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HVSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_VIDEO;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
		{
			name = L"VIDEO" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HVSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool(L"HOSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_OTHERS;

		AllHide();

		wstring name;

		for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
		{
			name = L"OTHERS" + to_wstring(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool(L"HOSB", VAR::ACTIVATION_FLAG, FALSE);
	}

	//Ç±Ç±Ç…ÉwÉbÉ_Å[èàóùÇèëÇ≠Å@ÅiÇsÇ`ÇaêÿÇËë÷Ç¶ìôÅjÅ@
}

void HEADER_Scene::Draw()
{

	DrawBox(0, 0, 350, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);
	DrawBox(1400, 0, 1920, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);

}

void HEADER_Scene::AllHide()
{
	wstring name;

	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		name = L"HOME" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
	{
		name = L"APP" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		name = L"GAME" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
	{
		name = L"MODEL" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
	{
		name = L"MUSIC" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
	{
		name = L"VIDEO" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
	{
		name = L"OTHERS" + to_wstring(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	return;
}
