#include "TAB_HOME_Scene.hpp"


TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager &objectManager)
	: SceneData(objectManager)
{
	objectManager.Set(L"test", 100, 100, 100, 100, BUTTON);
	objectManager.ColorSet(L"test", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
}