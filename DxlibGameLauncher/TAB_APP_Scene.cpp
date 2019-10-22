#include "TAB_APP_Scene.hpp"


TAB_APP_Scene::TAB_APP_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_APP_Scene::Update()
{
}

void TAB_APP_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"App");
}
