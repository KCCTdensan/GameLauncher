#include "DebugScene.h"

DebugScene::DebugScene() :
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(1200.f, 300.f), true, true),
	debugButton2(PosVec(50, 200.f), PosVec(75.f, 150.f), true, false),
	debugRect(PosVec(1100.f, 300.f), PosVec(300.f, 150.f), true, false),
	textSample1(PosVec(750, 700), PosVec(), FontData::GetFontHandle("mplus1"), "文字列", GetColor(135, 200, 56), TextAlign::CENTER, true)
{
	bg.SetInnerColor(GetColor(20, 20, 20));

	debugButton.SetInnerColor(GetColor(255, 255, 255), GetColor(230, 230, 230), GetColor(150, 150, 150), GetColor(200, 200, 200));
	debugButton.SetOutlineColor(GetColor(132, 220, 75), 5);

	debugButton2.SetInnerColor(GetColor(255, 200, 255), GetColor(235, 180, 235), GetColor(170, 115, 170), GetColor(200, 145, 200));
	// debugButton2.SetOutlineColor(GetColor(240, 150, 50), 5);

	debugButton.RegisterChildren(&debugButton2); // 子要素

	debugRect.SetInnerColor(GetColor(68, 191, 172));

	textSample1.SetBackColor(GetColor(150, 70, 100));

	// フォント追加
	fonts.push_back(FontHandle("smart", "03スマートフォントUI", 100));
	fonts.push_back(FontHandle("smart64", "03スマートフォントUI", 64, 15));
	fonts.push_back(FontHandle("mplus1", "M PLUS 2", 64, 100));
}

DebugScene::~DebugScene()
{
	//FontData::DeleteFontHandle("smart");
	//OutputDebugString("\n\nFonthandle deleted\n\n");
}

void DebugScene::Collide()
{
	debugButton.Collide();
	debugButton2.Collide();
}

void DebugScene::Update()
{

	RegFonts();
	if (textSample1.SetFontHandle() < 0) textSample1.SetFontHandle(FontData::GetFontHandle("mplus1"));

	bg.Update();

	debugButton.Update();
	debugButton2.Update();

	debugRect.Update();

	textSample1.Update();

	if (debugButton.GetMouseClicked()) {
		debugButton.SetMouseOff();
		debugButton.Move(PosVec(10.f, 10.f));
	}

	if (debugButton2.GetMouseClicked()) {
		debugButton2.SetMouseOff();
		debugButton2.Move(PosVec(-20.f, -20.f));
	}
}

void DebugScene::Draw()
{
	bg.Draw();

	debugButton.Draw();
	debugButton2.Draw();

	debugRect.Draw();

	textSample1.Draw();

	DrawFormatStringFToHandle(500, 600, GetColor(255, 255, 255), FontData::GetFontHandle("smart"), "test");
	DrawFormatStringFToHandle(1000, 750, GetColor(255, 137, 255), FontData::GetFontHandle("smart64"), "(T_T)");
}
