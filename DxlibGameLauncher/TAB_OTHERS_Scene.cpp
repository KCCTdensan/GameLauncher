#include "TAB_OTHERS_Scene.hpp"


TAB_OTHERS_Scene::TAB_OTHERS_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_OTHERS_Scene::Update()
{
}

void TAB_OTHERS_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"Others");
}
