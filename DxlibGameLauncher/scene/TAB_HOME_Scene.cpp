#include "TAB_HOME_Scene.hpp"


namespace scene
{
	TAB_HOME_Scene::TAB_HOME_Scene(ObjectManager &objectManager)
		: SceneBase(objectManager)
	{

	}

	void TAB_HOME_Scene::initialize()
	{
		objectManager.Set(L"test", 100, 100, 100, 100, BUTTON);
		objectManager.ColorSet(L"test", FALSE, NULL, NULL, TRUE, GetColor(255, 255, 255));
	}
}