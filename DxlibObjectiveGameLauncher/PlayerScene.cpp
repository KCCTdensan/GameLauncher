#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
}

PlayerScene::PlayerScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	songTitle(nullptr), songAuthor(nullptr), songHandleName(nullptr)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	
	songTitle = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 50.f), PosVec(),
		"smart40", "テスト文字列", ColorPreset::textBlack);
	songAuthor = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 100.f), PosVec(),
		"smart20", "作成者名", ColorPreset::textBlack);
	songHandleName = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 125.f), PosVec(),
		"smart20", "123456", ColorPreset::textBlack);

	startButton = new ButtonObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 150.f),
		PosVec(100.f, 100.f), true, true);
	startButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	startButton->SetInnerAnimation(.1f);
	startButton->SetOutlineColor(ColorPreset::yellowButtonOuter, 3.f);

	playBar = new ProgressObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 100.f),
		PosVec(ApplicationPreference::GetBackgroundSize().x - 100.f, 50.f), false);
	playBar->GetSlider()->SetInnerColor(Color255());
	playBar->SetInnerColor(Color255(200, 200, 200));
	playBar->SetOutlineColor(Color255(0, 0, 0), 1.f);

	layer.AddObject(bg);

	layer.AddObject(songTitle);
	layer.AddObject(songAuthor);
	layer.AddObject(songHandleName);
	layer.AddObject(startButton);
	layer.AddObject(playBar);

	// フォント追加
	fonts.push_back(FontHandle("smart40", "03スマートフォントUI", 40, 15));
	fonts.push_back(FontHandle("smart20", "03スマートフォントUI", 20, 15));
}

PlayerScene::~PlayerScene()
{
}

void PlayerScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void PlayerScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();
}

void PlayerScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
