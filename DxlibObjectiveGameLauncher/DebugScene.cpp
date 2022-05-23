#include "DebugScene.h"

DebugScene::DebugScene() :
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(100.f, 300.f), true, true),
	debugButton2(PosVec(50, 200.f), PosVec(75.f, 150.f), true, false),
	debugRect(PosVec(1100.f,300.f), PosVec(300.f,150.f), true, false)
{
	bg.SetInnerColor(GetColor(20, 20, 20));

	debugButton.SetInnerColor(GetColor(255, 255, 255), GetColor(230, 230, 230), GetColor(150, 150, 150), GetColor(200, 200, 200));
	debugButton.SetOutlineColor(GetColor(132, 220, 75), 5);

	debugButton2.SetInnerColor(GetColor(255, 200, 255), GetColor(235, 180, 235), GetColor(170, 115, 170), GetColor(200, 145, 200));
	// debugButton2.SetOutlineColor(GetColor(240, 150, 50), 5);

	debugButton.RegisterChildren(&debugButton2); // Žq—v‘f

	debugRect.SetInnerColor(GetColor(68, 191, 172));
}

void DebugScene::Update()
{
	debugButton.Collide();
	debugButton2.Collide();

	Header::Collide();

	bg.Update();

	debugButton.Update();
	debugButton2.Update();

	debugRect.Update();

	Header::Update();

	if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
		debugButton.Move(PosVec(10.f, 10.f));
		//SceneManager::ChangeScene("home", new HomeScene(), false);
	}

	if (debugButton2.GetMouseClicked()) {
		debugButton2.SetMouseOff();
		debugButton2.Move(PosVec(-20.f, -20.f));
		//SceneManager::ChangeScene("home", new HomeScene(), false);
	}
}

void DebugScene::Draw()
{
	bg.Draw();

	debugButton.Draw();
	debugButton2.Draw();

	debugRect.Draw();

	Header::Draw();
}
