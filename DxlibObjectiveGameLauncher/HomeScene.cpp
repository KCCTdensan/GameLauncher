#include "HomeScene.h"

HomeScene::HomeScene()
	: debugButton(PosVec(400, 700)
		, PosVec(500.f, 300.f))
{
	debugButton.SetInnerColor(Color255(252, 200, 0), Color255(222, 170, 0), Color255(172, 120, 0), Color255(202, 150, 0));
	debugButton.SetEnabledOutline(false);
}

void HomeScene::Collide()
{
	debugButton.Collide();
}

void HomeScene::Update()
{
	debugButton.Update();

	if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
		SceneManager::ChangeScene("debug", new DebugScene(), false);
	}
}

void HomeScene::Draw()
{
	debugButton.Draw();
}
