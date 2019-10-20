#include "TAB_HOME_Scene.hpp"


TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager& objectManager)
	: SceneData(objectManager)
{
	objectManager.Set(L"test", 100, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"test", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"test", TRUE, L"DEBUG");
	objectManager.WritingFontSet(L"test", OBJECT_FONT_GOTHIC, 30, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);
	objectManager.ImageChestSet(L"test", TRUE, L"D:\\Users\\seiya\\Desktop\\ñ≥ëË.png", 100, 100, 0, 0);

	objectManager.Set(L"testb", 300, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"testb", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"testb", TRUE, L"DEBUG");
	objectManager.WritingFontSet(L"testb", OBJECT_FONT_GOTHIC, 30, GetColor(0, 0, 0), ARRANGEMENT_X_CENTER, ARRANGEMENT_Y_CENTER);
	objectManager.ImageChestSet(L"testb", TRUE, L"D:\\Users\\seiya\\Desktop\\ñ≥ëË.png", 100, 100, 0, 0);
}

void TAB_HOME_Scene::Update()
{
	// ëIÇŒÇÍÇΩî‘çÜÇéÊìæÇµÇƒÇªÇÍÇ…î∫Ç¡ÇΩï\é¶ÇÇ≥ÇπÇÈ
}

void TAB_HOME_Scene::Draw()
{
	
	//DrawFormatString(0, 0, GetColor(255, 255, 255), L"x: %d", Input::Mouse::MOUSE_WIN_X);
}
