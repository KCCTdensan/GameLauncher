#include "TAB_MUSIC_Scene.hpp"


TAB_MUSIC_Scene::TAB_MUSIC_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_MUSIC_Scene::Update()
{
}

void TAB_MUSIC_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Music");
}
