#include "HomeScene.h"

HomeScene::HomeScene()
	:debugButton(PosVec(400,700), PosVec(500.f, 300.f))
{
	debugButton.SetInnerColor(GetColor(252, 200, 0), GetColor(222, 170, 0), GetColor(172, 120, 0), GetColor(202, 150, 0));
	debugButton.SetEnabledOutline(false);
}

void HomeScene::Update()
{
	debugButton.Collide();

	Header::Collide();

	debugButton.Update();

	Header::Update();

	if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
		SceneManager::ChangeScene("debug", new DebugScene(), false);
	}
}

void HomeScene::Draw()
{
	debugButton.Draw();

	Header::Draw();
}
