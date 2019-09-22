#include "TAB_HOME_Scene.h"
#include "OperationData.h"

using namespace Ope;

TAB_HOME_Scene::TAB_HOME_Scene()
{
	objectManager.Set("test", 100, 100, 100, 100, BUTTON);
	objectManager.ColorSet("test", FALSE, NULL, NULL, TRUE, GetColor(255,255,255));

}

void TAB_HOME_Scene::Update()
{
	objectManager.Update();
}

void TAB_HOME_Scene::Draw()
{
	objectManager.Draw();
}
