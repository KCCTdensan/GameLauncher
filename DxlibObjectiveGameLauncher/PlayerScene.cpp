#include "PlayerScene.h"

PlayerScene::PlayerScene()
	: bg(nullptr), loopButton(nullptr), nowPlaying(nullptr), playBar(nullptr), playListObject(nullptr),
	songTitle(nullptr), songAuthor(nullptr), songHandleName(nullptr), startButton(nullptr), canvas(nullptr)
{
}

PlayerScene::PlayerScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes), nowPlaying(nullptr),
	songTitle(nullptr), songAuthor(nullptr), songHandleName(nullptr), canvas(nullptr)
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
		PosVec(
			(ApplicationPreference::GetBackgroundSize().x - 100.f) / 2.f,
			ApplicationPreference::GetBackgroundSize().y - 200.f),
		PosVec(75.f, 75.f), true, true);
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
			(ApplicationPreference::GetBackgroundSize().x - 100.f) / 2.f - 100.f,
			ApplicationPreference::GetBackgroundSize().y - 200.f),
		PosVec(75.f, 75.f), true, true);
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
	playListObject->SetButtonListSample(new ButtonObject(PosVec(), PosVec(), true, true));
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

	canvas = new CanvasObject(
		PosVec(
			ApplicationPreference::GetBackgroundSize().x - 700.f,
			ApplicationPreference::startScenePos + 50.f),
		PosVec(600.f, 750.f), true, true);
	canvas->SetInnerColor(ColorPreset::tileInner);
	canvas->SetOutlineColor(ColorPreset::tileOuter, 2.f);

	canvas->RegisterChildren(playListObject);

	ideleteList = new InputObject(
		PosVec(
			ApplicationPreference::GetBackgroundSize().x - 800.f,
			ApplicationPreference::startScenePos + 50.f),
		PosVec(60, 20));
	ideleteList->SetupText(
		"smart20", ColorPreset::textBlack);
	ideleteList->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	ideleteList->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	ideleteList->SetInnerAnimation(.2f);

	bdeleteList = new ButtonObject(
		PosVec(
			ApplicationPreference::GetBackgroundSize().x - 730.f,
			ApplicationPreference::startScenePos + 50.f),
		PosVec(20, 20), true, true);
	bdeleteList->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	bdeleteList->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	bdeleteList->SetInnerAnimation(.2f);

	layer.AddObject(bg);

	layer.AddObject(songTitle);
	layer.AddObject(songAuthor);
	layer.AddObject(songHandleName);
	layer.AddObject(startButton);
	layer.AddObject(loopButton);
	layer.AddObject(playBar);
	layer.AddObject(playListObject);
	layer.AddObject(ideleteList);
	layer.AddObject(bdeleteList);

	canvases.AddObject(canvas);

	// フォント追加
	fonts.push_back(FontHandle("mplus40", "M PLUS 2", 40, 100));
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
			if (!MusicPlayer::GetPlaying())
				MusicPlayer::PlayInList(playStateRotater.GetNowState(), MusicPlayer::GetPlayingIndex(), false);
			else
				MusicPlayer::StopInList();
		}

	if (loopButton != nullptr)
		if (loopButton->GetMouseSelected()) {
			loopButton->SetMouseOff();
			playStateRotater.Rotate();
			MusicPlayer::SetPlayingState(playStateRotater.GetNowState());
		}

	if (playListObject->GetSelectingIndex() >= 0) {
		playListObject->SetMouseOffIndex();
		MusicPlayer::PlayInList(playStateRotater.GetNowState(), playListObject->GetSelectingIndex(), true);
	}

	if (songTitle != nullptr)
		songTitle->SetText(MusicPlayer::GetPlayingData().title);
	if (songAuthor != nullptr)
		songAuthor->SetText(MusicPlayer::GetPlayingData().author);
	if (songHandleName != nullptr) {
		std::string handleString = MusicPlayer::GetPlayingData().handle < 0 ? std::to_string(MusicPlayer::GetPlayingData().handle) : "Null";
		songHandleName->SetText(handleString);
	}

	if (playBar != nullptr) {
		if (playBar->GetMouseClicked())
			MusicPlayer::SetPlayingRate(playBar->GetValue());
		playBar->SetValue(MusicPlayer::GetPlayingRate());
	}

	if (playListObject != nullptr) {
		if (playListObject->SetList(MusicPlayer::GetPlayList(), "mplus40", PosVec(5.f, 5.f))) {
			canvas->DeleteAllChildren();
			canvas->RegisterChildren(playListObject);
			for (auto& item : playListObject->GetButtons()) {
				canvas->RegisterChildren(item);
			}
			if (playListObject->GetButtons().size() > 0)
				canvas->SetArea(PosVec(
					playListObject->GetButtons()[0]->GetSize().x,
					playListObject->GetButtons()[0]->GetSize().y * playListObject->GetButtons().size()),
					1.f / playListObject->GetButtons().size());
		}
	}

	if (bdeleteList != nullptr)
		if (bdeleteList->GetMouseSelected()) {
			bdeleteList->SetMouseOff();
			MusicPlayer::DeleteFromList(std::atoi(ideleteList->GetString().c_str()));
			ideleteList->RemakeHandle();
		}
}

void PlayerScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
