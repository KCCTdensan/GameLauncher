#include "TAB_HOME_Scene.hpp"


TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{
	objectManager.Set(L"test", 100, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"test", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	objectManager.WritingSet(L"test", TRUE, L"アイスクリーム");
	objectManager.WritingFontSet(L"test", 10, GetColor(255, 0, 255), ARRANGEMENT_X_LEFT, ARRANGEMENT_Y_CENTER);
}

void TAB_HOME_Scene::Update()
{
	objectManager.Update();
}

void TAB_HOME_Scene::Draw()
{
	objectManager.Draw();
	DrawFormatString(0, 0, GetColor(255, 255, 255), L"x: %d", Input::Mouse::MOUSE_WIN_X);
}
