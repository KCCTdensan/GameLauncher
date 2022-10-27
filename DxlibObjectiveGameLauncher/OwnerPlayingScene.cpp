#include "OwnerPlayingScene.h"
#include "PopupScene.h"

OwnerPlayingScene::OwnerPlayingScene()
{
}

OwnerPlayingScene::OwnerPlayingScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes), noticeGenerated(0), noticeGenerateNum(1)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(bg);

	canvas = new CanvasObject(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true);
	canvas->SetInnerColor(ColorPreset::transparent);

	const PosVec tileStartPos(190.f, ApplicationPreference::startScenePos + 200.f);
	const PosVec tileSize(200.f, 200.f);
	const PosVec tileGap(0.f, 0.f);
	const PosVec tileMass(tileSize.x + tileGap.x, tileSize.y + tileGap.y);

	title = new TextObject(
		PosVec(
			ApplicationPreference::GetBackgroundSize().x / 2.f,
			ApplicationPreference::startScenePos + 100.f), PosVec(),
		"mplus50", "タイトル", Color255(), TextAlign::CENTER);

	button1 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 0.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	button1->SetInnerColor(
		Color255(255, 0),
		Color255("#2AE0B2"),
		Color255("#27CEA4"),
		Color255("#CE82C6"));
	button1->SetOutlineColor(
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	button1->SetInnerAnimation(.2f);
	button1->SetOuterAnimation(.2f);

	button2 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	button2->SetInnerColor(
		Color255(250));
	button2->SetOutlineColor(
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	button2->SetRectWithEvent(MouseEventCase::HOVERED);
	button2->SetInnerAnimation(1.f);
	button2->SetOuterAnimation(.2f);

	button3 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 5.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, false);
	button3->SetInnerColor(
		Color255("#F4B658"),
		Color255("#F4CE95"),
		Color255("#F4CE95"),
		Color255("#F4CE95"));
	button3->SetInnerAnimation(0.f);

	button4 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 0.f,
			tileStartPos.y + tileMass.y * 1.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	button4->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	button4->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	button4->SetInnerAnimation(1.f);
	button4->SetOuterAnimation(.2f);

	button5 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 1.f),
		PosVec(
			tileSize.x * 6.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	button5->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	button5->SetOutlineColor(
		ColorPreset::yellowButtonOuter, 3.f);
	button5->SetInnerAnimation(.25f);
	button5->SetOuterAnimation(.2f);
	button5->SetupText("mplus100", "通知生成", ColorPreset::textObject);

	button6 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 7.f,
			tileStartPos.y + tileMass.y * 1.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * .5f + tileGap.y * 0.f), true, true);
	button6->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	button6->SetOutlineColor(
		ColorPreset::yellowButtonOuter, 3.f);
	button6->SetInnerAnimation(.25f);
	button6->SetOuterAnimation(.2f);
	button6->SetupText("mplus50", "↑", ColorPreset::textObject);

	button7 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 7.f,
			tileStartPos.y + tileMass.y * 1.5f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * .5f + tileGap.y * 0.f), true, true);
	button7->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	button7->SetOutlineColor(
		ColorPreset::yellowButtonOuter, 3.f);
	button7->SetInnerAnimation(.25f);
	button7->SetOuterAnimation(.2f);
	button7->SetupText("mplus50", "↓", ColorPreset::textObject);

	input1 = new InputObject(
		PosVec(
			tileStartPos.x + tileMass.x * 2.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 3.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), 1024);
	input1->SetupText("mplus30", ColorPreset::textBlack);
	input1->SetEnabledOutline(true);
	input1->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	input1->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	input1->SetInnerAnimation(.2f);
	input1->SetString("ここにテキストを入力");

	rect1 = new RectangleObject(
		PosVec(
			tileStartPos.x + tileMass.x * 7.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true);
	rect1->SetInnerColor(Color255("#F495C3"));

	progress1 = new ProgressObject(
		PosVec(
			tileStartPos.x + tileMass.x * 6.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), false);
	progress1->SetupSlider();
	progress1->SetEnabledOutline(true);
	progress1->GetSlider()->SetInnerColor(Color255());
	progress1->GetSlider()->SetInnerColor(
		Color255("#73D4C7"));
	progress1->SetInnerColor(Color255(200, 200, 200));
	progress1->SetOutlineColor(Color255(0, 0, 0), 1.f);
	progress1->SetValue(.4f);

	canvas->RegisterChildren(title);
	canvas->RegisterChildren(button1);
	canvas->RegisterChildren(button2);
	canvas->RegisterChildren(button3);
	canvas->RegisterChildren(button4);
	canvas->RegisterChildren(button5);
	canvas->RegisterChildren(button6);
	canvas->RegisterChildren(button7);
	canvas->RegisterChildren(input1);
	canvas->RegisterChildren(rect1);
	canvas->RegisterChildren(progress1);

	layer.AddObject(title);
	layer.AddObject(button1);
	layer.AddObject(button2);
	layer.AddObject(button3);
	layer.AddObject(button4);
	layer.AddObject(button5);
	layer.AddObject(button6);
	layer.AddObject(button7);
	layer.AddObject(input1);
	layer.AddObject(rect1);
	layer.AddObject(progress1);
	//
	int tileNumY = 5;

	canvas->SetArea(PosVec(
		ApplicationPreference::GetBackgroundSize().x,
		ApplicationPreference::startScenePos + tileSize.y * (float)tileNumY),
		tileSize.y / ((float)tileNumY * tileSize.y) / 2.f
	);
	canvases.AddObject(canvas);


	fonts.push_back(FontHandle("mplus100", "M PLUS 2", 100, 100));
	fonts.push_back(FontHandle("mplus50", "M PLUS 2", 50, 100));
	fonts.push_back(FontHandle("mplus30", "M PLUS 2", 30, 100));
}

void OwnerPlayingScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void OwnerPlayingScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();

	SetMiddleCenterText(button5);
	SetMiddleCenterText(button6);
	SetMiddleCenterText(button7);

	if (rect1 != nullptr && button3 != nullptr) {
		if (button3->GetMouseHit()) {
			rect1->ChangeColorWithAnimation(rect1->GetColor(ColorType::INNER), new Color255("#9B95F4"), .5f);
		}
		else {
			rect1->ChangeColorWithAnimation(rect1->GetColor(ColorType::INNER), new Color255("#F495C3"), .5f);
		}
	}

	if (button5 != nullptr && input1 != nullptr)
		if (button5->GetMouseSelected()) {
			button5->SetMouseOff();
			for (int i = 0; i < noticeGenerateNum; i++)
				sharingScenes->popupScene->MakeNotice(input1->GetString(), "ORIGINAL");
		}

	if (title != nullptr) {
		title->SetText(input1->GetString());
	}

	if (button6 != nullptr && button7 != nullptr) {
		if (button7->GetMouseSelected()) {
			button7->SetMouseOff();
			noticeGenerateNum--;
			std::string notice = "通知生成数: " + std::to_string(noticeGenerateNum);
			if (noticeGenerateNum < 1) {
				noticeGenerateNum = 1;
				notice = "通知生成数を1より少ない値にすることはできません";
			}
			sharingScenes->popupScene->MakeNotice(notice);
		}
		if (button6->GetMouseSelected()) {
			button6->SetMouseOff();
			noticeGenerateNum++;
			std::string notice = "通知生成数: " + std::to_string(noticeGenerateNum);
			sharingScenes->popupScene->MakeNotice(notice);
		}
	}

}

void OwnerPlayingScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}

void OwnerPlayingScene::SetMiddleCenterText(ButtonObject* button)
{
	if (button != nullptr) {
		button->GetTextObject()->SetPos(button->GetPos());
		button->GetTextObject()->Move(PosVec(
			(button->GetSize().x - button->GetTextObject()->GetTextWidth()) / 2.f,
			(button->GetSize().y - button->GetTextObject()->GetTextHeight()) / 2.f));
		button->GetTextObject()->SetForcedArea(
			button->GetPos(),
			PosVec(button->GetPos().x + button->GetSize().x, button->GetPos().y + button->GetSize().y));

	}
}
