#include "TAB_3DMODEL_Scene.hpp"


TAB_3DMODEL_Scene::TAB_3DMODEL_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{

}

void TAB_3DMODEL_Scene::Update()
{
}

void TAB_3DMODEL_Scene::Draw()
{
	DrawFormatStringToHandle(410, 50, GetColor(255, 255, 255), objectManager.GetHandleFont(L"G50"), L"3D Model");
}
