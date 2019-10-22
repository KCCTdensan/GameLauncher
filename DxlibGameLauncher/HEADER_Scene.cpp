#include "HEADER_Scene.h"

HEADER_Scene::HEADER_Scene(ObjectManager& objectManager)
{
	objectManager.Set(L"HHSB", 50, 350, 250, 100, BUTTON);
	objectManager.ColorSet(L"HHSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HHSB", TRUE, L"Home");
	objectManager.WritingFontSetToHandle(L"HHSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HASB", 50, 450, 250, 100, BUTTON);
	objectManager.ColorSet(L"HASB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HASB", TRUE, L"App");
	objectManager.WritingFontSetToHandle(L"HASB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HGSB", 50, 550, 250, 100, BUTTON);
	objectManager.ColorSet(L"HGSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HGSB", TRUE, L"Game");
	objectManager.WritingFontSetToHandle(L"HGSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"H3SB", 50, 650, 250, 100, BUTTON);
	objectManager.ColorSet(L"H3SB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"H3SB", TRUE, L"3D Model");
	objectManager.WritingFontSetToHandle(L"H3SB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HMSB", 50, 750, 250, 100, BUTTON);
	objectManager.ColorSet(L"HMSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HMSB", TRUE, L"Music");
	objectManager.WritingFontSetToHandle(L"HMSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HVSB", 50, 850, 250, 100, BUTTON);
	objectManager.ColorSet(L"HVSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HVSB", TRUE, L"Video");
	objectManager.WritingFontSetToHandle(L"HVSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HOSB", 50, 950, 250, 100, BUTTON);
	objectManager.ColorSet(L"HOSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HOSB", TRUE, L"Others");
	objectManager.WritingFontSetToHandle(L"HOSB", L"G50", GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HPicKCCT", 50, 50, 250, 250, PICTURE);
	objectManager.ImageChestSet(L"HPicKCCT", TRUE, L".\\pic\\KCCTicon.png", 0, 0);

	manager = &objectManager;

}

void HEADER_Scene::Update()
{
	if (manager->GetVarBool(L"HHSB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_HOME;
	}
	if (manager->GetVarBool(L"HASB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_APP;
	}
	if (manager->GetVarBool(L"HGSB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_GAME;
	}
	if (manager->GetVarBool(L"H3SB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_3DMODEL;
	}
	if (manager->GetVarBool(L"HMSB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_MUSIC;
	}
	if (manager->GetVarBool(L"HVSB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_VIDEO;
	}
	if (manager->GetVarBool(L"HOSB", ACTIVATION_FLAG)) {
		Ope::SCENE_CHANGE_FLAG = TRUE;
		Ope::SCENE_CHANGE_NUM = TAB_OTHERS;
	}

	//ここにヘッダー処理を書く　（ＴＡＢ切り替え等）　
}

void HEADER_Scene::Draw()
{

	DrawBox(0, 0, 350, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);
	DrawBox(1400, 0, 1920, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);

}
