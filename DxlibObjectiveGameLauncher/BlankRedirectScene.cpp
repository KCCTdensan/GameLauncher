#include "BlankRedirectScene.h"

void BlankRedirectScene::Update()
{
	SceneManager::ChangeScene("Home", new HomeScene());
}
