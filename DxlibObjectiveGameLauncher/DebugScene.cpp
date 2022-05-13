#include "DebugScene.h"

DebugScene::DebugScene()
	:debugButton(PosVec(),PosVec(100.f,300.f),true,true)
{
	debugButton.SetInnerColor(GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255));
	debugButton.SetOutlineColor(GetColor(132, 220, 75), 5);
}

void DebugScene::Update()
{
	debugButton.Update();
}

void DebugScene::Draw()
{
	debugButton.Draw();
}
