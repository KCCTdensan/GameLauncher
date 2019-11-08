#include "HEADER_Scene.h"

#include "InputManager.h"

HEADER_Scene::HEADER_Scene(ObjectManager& objectManager, MusicManager& musicManager, Json& json, JsonManager& jsonManager)
{
	defJson = {
		"NONE",
		"",
		"",
		"",
		"NONE"
	};

	json = defJson;

	Ope::JSON_MUSIC_FLAG = FALSE;

	PlayingNotice = FALSE;

	objectManager.Set("HHSB", 50, 350, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HHSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HHSB", TRUE, "Home");
	objectManager.WritingFontSetToHandle("HHSB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HASB", 50, 450, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HASB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HASB", TRUE, "App");
	objectManager.WritingFontSetToHandle("HASB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HGSB", 50, 550, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HGSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HGSB", TRUE, "Game");
	objectManager.WritingFontSetToHandle("HGSB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("H3SB", 50, 650, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("H3SB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("H3SB", TRUE, "3D Model");
	objectManager.WritingFontSetToHandle("H3SB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HMSB", 50, 750, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HMSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HMSB", TRUE, "Music");
	objectManager.WritingFontSetToHandle("HMSB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HVSB", 50, 850, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HVSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HVSB", TRUE, "Video");
	objectManager.WritingFontSetToHandle("HVSB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HOSB", 50, 950, 250, 100, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HOSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("HOSB", TRUE, "Others");
	objectManager.WritingFontSetToHandle("HOSB", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set("HPicKCCT", 50, 50, 250, 250, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("HPicKCCT", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.ImageChestSet("HPicKCCT", TRUE, ".\\Content\\Pic\\KCCTicon.png", 0, 0);
	objectManager.ChangeVarBool("HPicKCCT", VAR::ANIMATION_FLAG, FALSE);

	objectManager.Set("Launch", 1450, 880, 420, 150, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("Launch", TRUE, GetColor(255, 190, 0), 3, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet("Launch", TRUE, "Launch");
	objectManager.WritingFontSetToHandle("Launch", "G50", GetColor(255, 255, 255), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);

	objectManager.Set("MusicPlay", 420, 990, 50, 50, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("MusicPlay", FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
	objectManager.ImageChestSet("MusicPlay", TRUE, ".\\Content\\Pic\\PlayMusic.png", 0, 0);

	objectManager.Set("MusicStop", 420, 990, 50, 50, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("MusicStop", FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
	objectManager.ImageChestSet("MusicStop", TRUE, ".\\Content\\Pic\\StopMusic.png", 0, 0);

	objectManager.Set("MusicClear", 1020, 940, 25, 25, OBJECT_TYPE::BUTTON);
	objectManager.ColorSet("MusicClear", FALSE, NULL, NULL, TRUE, GetColor(BLACK + 20, BLACK + 20, BLACK + 20));
	objectManager.ImageChestSet("MusicClear", TRUE, ".\\Content\\Pic\\ClearMusic.png", 0, 0);

	//musicManager.Set("Debug", ".\\Content\\Software\\MUSIC\\Vacation.mp3");
	//musicManager.Play("Debug");

	objectManager.Set("MusicProgress", 500, 998, 500, 24, OBJECT_TYPE::PROGRESS);
	objectManager.ProgressSet("MusicProgress", TRUE, GetColor(0, 128, 255), GetColor(BLACK, BLACK, BLACK));

	this->objectManager = &objectManager;
	this->musicManager = &musicManager;
	this->json = &json;
}

void HEADER_Scene::Update()
{
	if (objectManager->GetVarBool("HPicKCCT", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_HOME;

		AllHide();

		string name;

		for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
		{
			name = "HOME" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HPicKCCT", VAR::ACTIVATION_FLAG, FALSE);

		//json = &defJson;
	}
	if (objectManager->GetVarBool("HHSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_HOME;

		AllHide();

		string name;

		for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
		{
			name = "HOME" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HHSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("HASB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_APP;

		AllHide();

		string name;

		for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
		{
			name = "APP" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HASB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("HGSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_GAME;

		AllHide();

		string name;

		for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
		{
			name = "GAME" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HGSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("H3SB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_3DMODEL;

		AllHide();

		string name;

		for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
		{
			name = "MODE" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("H3SB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("HMSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_MUSIC;

		AllHide();

		string name;

		for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
		{
			name = "MUSIC" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HMSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("HVSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_VIDEO;

		AllHide();

		string name;

		for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
		{
			name = "VIDEO" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HVSB", VAR::ACTIVATION_FLAG, FALSE);
	}
	if (objectManager->GetVarBool("HOSB", VAR::ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = SCENE::TAB_OTHERS;

		AllHide();

		string name;

		for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
		{
			name = "OTHERS" + to_string(i);

			objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, TRUE);
		}

		objectManager->ChangeVarBool("HOSB", VAR::ACTIVATION_FLAG, FALSE);
	}

	if (objectManager->GetVarBool("Launch", VAR::ACTIVATION_FLAG)) {

		if (Ope::JSON_MUSIC_FLAG)
		{
			musicManager->Stop(musicManager->GetPlayingName());
			musicManager->DeleteAll();
			musicManager->Set(json->name, json->path);
			musicManager->Replay(json->name);
		}
		else if (Ope::JSON_VIDEO_FLAG)
		{
			string a = "wmplayer.exe /play \""+ json->path+"\"";
			system(a.c_str());

		}
		else {

			system(json->path.c_str());

		}
		objectManager->ChangeVarBool("Launch", VAR::ACTIVATION_FLAG, FALSE);

	}

	if (json->name == "NONE")
	{
		objectManager->ChangeVarBool("Launch", VAR::CAN_SEE_FLAG, FALSE);
	}
	else {
		objectManager->ChangeVarBool("Launch", VAR::CAN_SEE_FLAG, TRUE);
	}

	if (PlayingNotice = musicManager->GetPlaying()) {
		PlayingNotice = TRUE;
	}
	else {
		PlayingNotice = FALSE;
	}
	PlayingName = musicManager->GetPlayingName();

	if (musicManager->GetDoingOutput())
	{
		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, TRUE);
	}
	else {
		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, TRUE);
		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, FALSE);
	}

	if (!PlayingNotice)
	{
		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicClear", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicProgress", VAR::CAN_SEE_FLAG, FALSE);
	}
	else {
		objectManager->ChangeVarBool("MusicClear", VAR::CAN_SEE_FLAG, TRUE);
		objectManager->ChangeVarBool("MusicProgress", VAR::CAN_SEE_FLAG, TRUE);
	}

	float a = musicManager->GetNowPosition();
	float b = musicManager->GetTotalTime();
	float c = a / b;
	objectManager->ChangeProgress("MusicProgress", c);

	/*if (musicManager->GetNowPosition() >= musicManager->GetTotalTime() && musicManager->GetDoingOutput())
	{
		musicManager->Stop(PlayingName);

		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, TRUE);
	}*/

	if (objectManager->GetVarBool("MusicPlay", VAR::ACTIVATION_FLAG)) {

		if (musicManager->GetNowPosition() >= musicManager->GetTotalTime())
		{
			musicManager->Replay(PlayingName);
		}
		else {
			musicManager->Play(PlayingName);
		}

		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, TRUE);

	}
	if (objectManager->GetVarBool("MusicStop", VAR::ACTIVATION_FLAG)) {

		musicManager->Stop(PlayingName);

		objectManager->ChangeVarBool("MusicStop", VAR::CAN_SEE_FLAG, FALSE);
		objectManager->ChangeVarBool("MusicPlay", VAR::CAN_SEE_FLAG, TRUE);

	}
	if (objectManager->GetVarBool("MusicClear", VAR::ACTIVATION_FLAG)) {

		musicManager->Stop(PlayingName);

		musicManager->DeleteAll();

	}
}

void HEADER_Scene::Draw()
{

	DrawBox(0, 0, 350, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);
	DrawBox(1400, 0, 1920, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);

	//DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), objectManager->GetHandleFont("G30"), "%d", Input::Mouse::MOUSE_LEFT);

	if (json->name != "NONE") {

		DrawFormatStringToHandle(1450, 50, GetColor(255, 255, 255), objectManager->GetHandleFont("G50"), "%s", json->name.c_str());//タイトル
		DrawFormatStringToHandle(1450, 150, GetColor(255, 255, 255), objectManager->GetHandleFont("G30"), "Version : %s", json->version.c_str());
		DrawFormatStringToHandle(1450, 300, GetColor(255, 255, 255), objectManager->GetHandleFont("G20"), "%s", json->explanation.c_str());
	}
	else {
		DrawFormatStringToHandle(1450, 150, GetColor(255, 255, 255), objectManager->GetHandleFont("G30"), "左の一覧からファイル・ソフトを\n選んでください");
	}


	if (PlayingNotice) {

		DrawRoundRect(400, 940, 1050, 1050, 10, 10, GetColor(BLACK + 20, BLACK + 20, BLACK + 20), TRUE);
		DrawFormatStringToHandle(420, 950, GetColor(255, 255, 255), objectManager->GetHandleFont("G30"), "再生中... : %s ", musicManager->GetPlayingName().c_str());

	}

}

void HEADER_Scene::AllHide()
{
	string name;

	for (int i = 0; i < Ope::HOME_BUTTON_NUM; i++)
	{
		name = "HOME" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::APP_BUTTON_NUM; i++)
	{
		name = "APP" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::GAME_BUTTON_NUM; i++)
	{
		name = "GAME" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MODEL_BUTTON_NUM; i++)
	{
		name = "MODE" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::MUSIC_BUTTON_NUM; i++)
	{
		name = "MUSIC" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::VIDEO_BUTTON_NUM; i++)
	{
		name = "VIDEO" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}
	for (int i = 0; i < Ope::OTHERS_BUTTON_NUM; i++)
	{
		name = "OTHERS" + to_string(i);

		objectManager->ChangeVarBool(name.c_str(), VAR::CAN_SEE_FLAG, FALSE);
	}

	return;
}
