#include "PlayerScene.h"

PlayerScene::PlayerScene()
{
}

PlayerScene::PlayerScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes), nowPlaying(nullptr),
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
	playBar->SetupSlider();
	playBar->GetSlider()->SetInnerColor(Color255());
	playBar->GetSlider()->SetInnerColor(
		Color255("#73D4C7"));
	playBar->SetInnerColor(Color255(200, 200, 200));
	playBar->SetOutlineColor(Color255(0, 0, 0), 1.f);

	loopButton = new ButtonObject(
		PosVec(
			(ApplicationPreference::GetBackgroundSize().x - 100.f) / 2.f,
			ApplicationPreference::GetBackgroundSize().y - 150.f),
		PosVec(100.f, 100.f), true, true);
	loopButton->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	loopButton->SetOutlineColor(
		ColorPreset::tileOuter,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse, 2.f);

	playListObject = new PlayListObject(
		PosVec(
			ApplicationPreference::GetBackgroundSize().x - 700.f,
			ApplicationPreference::startScenePos + 50.f),
		PosVec(600.f, 750.f));
	playListObject->SetInnerColor(ColorPreset::tileInner);
	playListObject->SetListHeight(100.f);
	playListObject->SetOutlineColor(ColorPreset::tileOuter, 2.f);
	playListObject->GetButtonListSample(&ButtonObject(PosVec(), PosVec(), true, true));
	playListObject->GetButtonListSample()->SetInnerColor(
		ColorPreset::navLinksInner,
		ColorPreset::navLinksHovered,
		ColorPreset::navLinksClicked,
		ColorPreset::navLinksSelected);
	playListObject->GetButtonListSample()->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 2.f);

	layer.AddObject(bg);

	layer.AddObject(songTitle);
	layer.AddObject(songAuthor);
	layer.AddObject(songHandleName);
	layer.AddObject(startButton);
	layer.AddObject(loopButton);
	layer.AddObject(playBar);
	layer.AddObject(playListObject);

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

	if (startButton != nullptr)
		if (startButton->GetMouseSelected()) {
			startButton->SetMouseOff();
			MusicPlayer::PlayInList(PlayState::SIMPLE, 0, true);
		}

	if (songTitle != nullptr)
		songTitle->SetText(MusicPlayer::GetPlayingData().title);
	if (songAuthor != nullptr)
		songAuthor->SetText(MusicPlayer::GetPlayingData().author);
	if (songHandleName != nullptr) {
		std::string handleString = MusicPlayer::GetPlayingData().handle < 0 ? std::to_string(MusicPlayer::GetPlayingData().handle) : "Null";
		songHandleName->SetText(handleString);
	}

	if (playBar->GetMouseClicked())
		MusicPlayer::SetPlayingRate(playBar->GetValue());
	playBar->SetValue(MusicPlayer::GetPlayingRate());

	playListObject->SetList(MusicPlayer::GetPlayList());
}

void PlayerScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
