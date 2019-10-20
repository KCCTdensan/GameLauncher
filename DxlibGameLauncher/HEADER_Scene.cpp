#include "HEADER_Scene.h"

HEADER_Scene::HEADER_Scene(ObjectManager& objectManager)
{
	objectManager.Set(L"HHSB", 50, 250, 250, 100, BUTTON);
	objectManager.ColorSet(L"HHSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HHSB", TRUE, L"Home");
	objectManager.WritingFontSet(L"HHSB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HASB", 50, 350, 250, 100, BUTTON);
	objectManager.ColorSet(L"HASB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HASB", TRUE, L"App");
	objectManager.WritingFontSet(L"HASB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HGSB", 50, 450, 250, 100, BUTTON);
	objectManager.ColorSet(L"HGSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HGSB", TRUE, L"Game");
	objectManager.WritingFontSet(L"HGSB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"H3SB", 50, 550, 250, 100, BUTTON);
	objectManager.ColorSet(L"H3SB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"H3SB", TRUE, L"3D Model");
	objectManager.WritingFontSet(L"H3SB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HMSB", 50, 650, 250, 100, BUTTON);
	objectManager.ColorSet(L"HMSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HMSB", TRUE, L"Music");
	objectManager.WritingFontSet(L"HMSB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HVSB", 50, 750, 250, 100, BUTTON);
	objectManager.ColorSet(L"HVSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HVSB", TRUE, L"Video");
	objectManager.WritingFontSet(L"HVSB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

	objectManager.Set(L"HOSB", 50, 850, 250, 100, BUTTON);
	objectManager.ColorSet(L"HOSB", FALSE, NULL, NULL, TRUE, GetColor(BLACK, BLACK, BLACK));
	objectManager.WritingSet(L"HOSB", TRUE, L"Others");
	objectManager.WritingFontSet(L"HOSB", OBJECT_FONT_GOTHIC, 50, GetColor(255, 255, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);

}

void HEADER_Scene::Update()
{
	//Ç±Ç±Ç…ÉwÉbÉ_Å[èàóùÇèëÇ≠Å@ÅiÇsÇ`ÇaêÿÇËë÷Ç¶ìôÅjÅ@
}

void HEADER_Scene::Draw()
{

	DrawBox(0, 0, 350, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);
	DrawBox(1400, 0, 1920, 1080, GetColor(BLACK, BLACK, BLACK), TRUE);

}
