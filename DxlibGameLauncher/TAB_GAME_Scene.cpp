#include "TAB_GAME_Scene.hpp"


TAB_GAME_Scene::TAB_GAME_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_GAME_Scene::Update()
{
}

void TAB_GAME_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Game");

}
