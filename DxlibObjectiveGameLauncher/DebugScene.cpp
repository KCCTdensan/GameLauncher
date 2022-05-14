#include "DebugScene.h"

DebugScene::DebugScene() :
	debugButton(PosVec(), PosVec(100.f, 300.f), true, true),
	debugButton2(PosVec(200.f, 200.f), PosVec(75.f, 150.f), true, true)
{
	debugButton.SetInnerColor(GetColor(255, 255, 255), GetColor(230, 230, 230), GetColor(150, 150, 150), GetColor(200, 200, 200));
	debugButton.SetOutlineColor(GetColor(132, 220, 75), 5);

	debugButton2.SetInnerColor(GetColor(255, 200, 255), GetColor(130, 130, 130), GetColor(255, 255, 255), GetColor(255, 255, 255));
	debugButton2.SetOutlineColor(GetColor(240, 150, 50), 5);
}

void DebugScene::Update()
{
	debugButton.Update();
	debugButton2.Update();
}

void DebugScene::Draw()
{
	debugButton.Draw();
	debugButton2.Draw();
}
