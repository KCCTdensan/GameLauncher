#include "DebugScene.h"

DebugScene::DebugScene() :
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(1200.f, 300.f), true, true),
	debugButton2(PosVec(50, 200.f), PosVec(75.f, 150.f), true, true),
	debugRect(PosVec(1100.f, 300.f), PosVec(300.f, 150.f), true, false),
	textSample1(PosVec(750, 700), PosVec(), "mplus1", "文字列", Color255(135, 200, 56), TextAlign::CENTER, true),
	input(PosVec(500,500), PosVec(200,100)),
	input2(PosVec(900,800), PosVec(200,100))
{
	bg.SetInnerColor(Color255(20, 20, 20));

	/*debugButton.SetInnerColor(
		Color255(255, 255, 255),
		Color255(230, 230, 230),
		Color255(150, 150, 150, 200),
		Color255(200, 200, 200));*/
	debugButton.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	debugButton.SetOutlineColor(
		Color255(132, 220, 75, 0),
		Color255(100, 190, 75, 255),
		Color255(86, 170, 50),
		Color255(110, 200, 75), 5);
	debugButton.SetInnerAnimation(.3f);
	debugButton.SetOuterAnimation(.3f);
	
	debugButton2.SetInnerColor(Color255(255, 200, 255, 0), Color255(235, 180, 235, 255), Color255(170, 115, 170, 100), Color255(200, 145, 200));
	debugButton2.SetInnerAnimation(.4f);
	debugButton2.SetOutlineColor(Color255(255, 150, 50), 5);
	debugButton2.SetOuterAnimation(.4f);

	debugButton.RegisterChildren(&debugButton2); // 子要素

	debugRect.SetInnerColor(Color255(68, 191, 172));

	textSample1.SetBackColor(Color255(150, 70, 100));
	textSample1.SetPadding(10.f, 20.f, 5.f, 30.f);
	
	input.SetupText("smart15", Color255(135, 200, 56), TextAlign::LEFT);
	input.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	input.SetInnerAnimation(.2f);
	input.SetInterruptMode(false);

	input2.SetupText("smart15", Color255(255, 255, 255), TextAlign::CENTER);
	input2.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	input2.SetInnerAnimation(.2f);
	input2.SetInterruptMode(true);

	// フォント追加
	fonts.push_back(FontHandle("smart", "03スマートフォントUI", 100));
	fonts.push_back(FontHandle("smart64", "03スマートフォントUI", 64, 15));
	fonts.push_back(FontHandle("smart15", "03スマートフォントUI", 20, 15));
	fonts.push_back(FontHandle("mplus1", "M PLUS 2", 64, 100));
}

DebugScene::~DebugScene()
{
	//FontChest::DeleteFontHandle("smart");
	//OutputDebugString("\n\nFonthandle deleted\n\n");
}

void DebugScene::Collide()
{
	debugButton.Collide();
	debugButton2.Collide();

	debugRect.Collide();

	input.Collide();
	input2.Collide();
}

void DebugScene::Update()
{

	RegFonts();
	//if (textSample1.SetFontHandle() < 0) textSample1.SetFontHandle(FontChest::GetFontHandle("mplus1"));

	bg.Update();

	debugButton.Update();
	debugButton2.Update();

	debugRect.Update();

	textSample1.Update();

	input.Update();
	input2.Update();

	if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
		debugButton.Move(PosVec(10.f, 10.f));
	}

	if (debugButton.GetMouseHit()) {
		input.GetTextObject()->ChangeColorWithAnimation(input.GetTextObject()->GetColor(ColorType::INNER), new Color255(255, 0, 0), 0.2f);
	}

	if (debugButton.GetMouseClicked()) {
		input.GetTextObject()->ChangeColorWithAnimation(input.GetTextObject()->GetColor(ColorType::INNER), new Color255(255, 255, 255), 0.2f);
	}

	if (debugButton2.GetMouseSelected()) {
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

	input.Draw();
	input2.Draw();

	DrawFormatStringFToHandle(500, 600, GetColor(255, 255, 255), FontChest::GetFontHandle("smart"), "test");
	DrawFormatStringFToHandle(1000, 750, GetColor(255, 137, 255), FontChest::GetFontHandle("smart64"), "(T_T)");
}
