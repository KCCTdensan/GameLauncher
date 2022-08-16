#include "DebugScene.h"

DebugScene::DebugScene() :
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(1200.f, 300.f), true, true),
	debugButton2(PosVec(150, 220.f), PosVec(100.f, 100.f), true, true),
	debugRect(PosVec(1100.f, 300.f), PosVec(300.f, 150.f), true, false),
	textSample1(PosVec(750, 700), PosVec(), "mplus1", "文字列", Color255(135, 200, 56), TextAlign::CENTER, true),
	input(PosVec(500, 500), PosVec(200, 100)),
	input2(PosVec(900, 800), PosVec(200, 100)),
	pallet(PosVec(1200, 300), PosVec(400, 400), true, false),
	canvas(PosVec(150, 150), PosVec(500, 500)),
	progress(PosVec(1200, 700), PosVec(50, 300), true, 0.13f)
{
	bg.SetInnerColor(Color255("#f4faf9"));
	layer.AddObject(&bg);

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
	
	debugButton2.SetInnerColor(
		Color255("#f6f8f8"),
		Color255("#f0f3f2"),
		Color255("#d6d8d8"),
		Color255("#f0f3f2"));
	debugButton2.SetInnerAnimation(.4f);
	debugButton2.SetOutlineColor(Color255(50, 50, 50), 1.2f);
	debugButton2.SetOuterAnimation(.4f);
	debugButton2.SetRectWithEvent(MouseEventCase::HOVERED, DirectionType::BOTTOM, Color255("#bdced5", 150));

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

	input2.SetupText("smart15", Color255(255, 255, 255), TextAlign::LEFT);
	input2.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	input2.SetInnerAnimation(.2f);
	input2.SetInterruptMode(false);

	pallet.SetInnerColor(Color255(255, 255, 255));

	progress.SetInnerColor(Color255(200, 200, 200));

	canvas.SetInnerColor(Color255(200,250,250));
	canvas.SetArea(PosVec(1000, 1000));

	layer.AddObject(&debugButton);
	layer.AddObject(&debugButton2);
	layer.AddObject(&debugRect);
	layer.AddObject(&textSample1);
	layer.AddObject(&input);
	layer.AddObject(&input2);
	layer.AddObject(&pallet);
	layer.AddObject(&progress);

	canvas.RegisterChildren(&debugButton);
	//canvas.RegisterChildren(&debugButton2);
	canvas.RegisterChildren(&debugRect);
	canvas.RegisterChildren(&textSample1);
	canvas.RegisterChildren(&input);
	//canvas.RegisterChildren(&input2);
	canvas.RegisterChildren(&pallet);

	canvases.AddObject(&canvas);

	// フォント追加
	fonts.push_back(FontHandle("smart", "03スマートフォントUI", 100));
	fonts.push_back(FontHandle("smart64", "03スマートフォントUI", 64, 15));
	fonts.push_back(FontHandle("smart15", "03スマートフォントUI", 20, 15));
	fonts.push_back(FontHandle("mplus1", "M PLUS 2", 64, 100));
}

DebugScene::~DebugScene()
{
	for (const auto& font : fonts) {
		FontChest::DeleteFontHandle(font.handleName);
	}
}

void DebugScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void DebugScene::Update()
{

	RegFonts();

	layer.Update();
	canvases.Update();

	/*if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
		debugButton.Move(PosVec(10.f, 10.f));
	}*/

	//if (bg.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(255, 255, 255), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(20, 20, 20), 1.f);
	//}

	//if (debugButton.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(255, 0, 0), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(128, 0, 0), 10.f);
	//}

	//if (debugButton2.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(0, 255, 0), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(0, 128, 0), 10.f);
	//}

	if (debugButton2.GetMouseSelected()) {
		Header::SetSubtitle("変更されたテキスト");
	}
	else if (debugButton2.GetMouseClicked()) {
		Header::SetSubtitle("変更しそうなテキスト");
	}
	else if(debugButton2.GetMouseHit()) {
		Header::SetSubtitle("変更するかもしれないテキスト");
	}
	else {
		Header::SetSubtitle("変更されていないテキスト");
	}

	//if (debugRect.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(0, 0, 255), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(0, 0, 128), 10.f);
	//}

	//if (debugButton.GetMouseClicked()) {
	//	input.GetTextObject()->ChangeColorWithAnimation(input.GetTextObject()->GetColor(ColorType::INNER), new Color255(255, 255, 255), 0.2f);
	//}

	//if (debugButton2.GetMouseSelected()) {
	//	debugButton2.SetMouseOff();
	//	debugButton2.Move(PosVec(-20.f, -20.f));
	//}
}

void DebugScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
