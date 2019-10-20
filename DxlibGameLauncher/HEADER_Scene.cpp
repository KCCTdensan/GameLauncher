#include "HEADER_Scene.h"

HEADER_Scene::HEADER_Scene(ObjectManager& objectManager)
{
	/*objectManager.Set(L"HHSB", 100, 250, 300, 100, BUTTON);
	objectManager.ColorSet(L"HHSB", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"HHSB", TRUE, L"HOME");
	objectManager.WritingFontSet(L"HHSB", OBJECT_FONT_GOTHIC, 50, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);*/

	//objectManager.Set(L"testA", 200, 100, 100, 100, BUTTON);
	//ColorSet(L"testA", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	//objectManager.WritingSet(L"testA", TRUE, L"DEBUG");
	//objectManager.WritingFontSet(L"testA", OBJECT_FONT_GOTHIC, 30, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);
	//objectManager.ImageChestSet(L"testA", TRUE, L"D:\\Users\\seiya\\Desktop\\無題.png", 100, 100, 0, 0);

	objectManager.Set(L"testa", 200, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"testa", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"testa", TRUE, L"DEBUG");
	objectManager.WritingFontSet(L"testa", OBJECT_FONT_GOTHIC, 30, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);
	objectManager.ImageChestSet(L"testa", TRUE, L"D:\\Users\\seiya\\Desktop\\無題.png", 100, 100, 0, 0);
}

void HEADER_Scene::Update()
{
	//ここにヘッダー処理を書く　（ＴＡＢ切り替え等）　
}

void HEADER_Scene::Draw()
{
}
