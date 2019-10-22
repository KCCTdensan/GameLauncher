#include "TAB_VIDEO_Scene.hpp"


TAB_VIDEO_Scene::TAB_VIDEO_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_VIDEO_Scene::Update()
{
}

void TAB_VIDEO_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Video");
}
