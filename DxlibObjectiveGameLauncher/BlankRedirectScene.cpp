#include "BlankRedirectScene.h"

void BlankRedirectScene::Update()
{
	SceneManager::ChangeScene("home", new HomeScene());
}
