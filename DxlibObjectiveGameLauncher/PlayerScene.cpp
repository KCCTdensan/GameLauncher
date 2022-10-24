#include "PlayerScene.h"
#include "PopupScene.h"

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

	nextLabel = new TextObject(
		PosVec(50.f, ApplicationPreference::startScenePos + 200.f), PosVec(),
		"smart20", "NEXT...", ColorPreset::textBlack);
	nextTitle = new TextObject(
		PosVec(70.f, ApplicationPreference::startScenePos + 225.f), PosVec(),
		"smart20", "NEXT TITLE", ColorPreset::textBlack);
	nextAuthor = new TextObject(
		PosVec(70.f, ApplicationPreference::startScenePos + 250.f), PosVec(),
		"smart20", "NEXT AUTHOR", ColorPreset::textBlack);

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
	startButton->SetImageSize(PosVec(75.f, 75.f));
	startButton->SetImageTurnFlag(false, false);

	playBar = new ProgressObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 100.f),
		PosVec(ApplicationPreference::GetBackgroundSize().x - 100.f, 50.f), false);
	playBar->SetupSlider();
	playBar->SetEnabledOutline(true);
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
	loopButton->SetImageSize(PosVec(75.f, 75.f));
	loopButton->SetImageTurnFlag(false, false);

	volumeBar = new ProgressObject(
		PosVec(
			(ApplicationPreference::GetBackgroundSize().x - 100.f) / 2.f + 100.f,
			ApplicationPreference::GetBackgroundSize().y - 200.f + 32.5f),
		PosVec(150.f, 32.5f), false);
	volumeBar->SetupSlider();
	volumeBar->SetEnabledOutline(true);
	volumeBar->GetSlider()->SetInnerColor(Color255());
	volumeBar->GetSlider()->SetInnerColor(
		Color255("#73D4C7"));
	volumeBar->SetInnerColor(Color255(200, 200, 200));
	volumeBar->SetOutlineColor(Color255(0, 0, 0), 1.f);
	volumeBar->SetValue(.4f);

	lvolume = new TextObject(
		PosVec(
			(ApplicationPreference::GetBackgroundSize().x - 100.f) / 2.f + 100.f,
			ApplicationPreference::GetBackgroundSize().y - 200.f), PosVec(),
		"smart20", "VOLUME", ColorPreset::textBlack);

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
			ApplicationPreference::GetBackgroundSize().x - 700.f,
			ApplicationPreference::startScenePos + 10.f),
		PosVec(200, 30), 40, true, true, true);
	ideleteList->SetupText(
		"smart20", ColorPreset::textBlack);
	ideleteList->SetEnabledOutline(true);
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
			ApplicationPreference::GetBackgroundSize().x - 480.f,
			ApplicationPreference::startScenePos + 10.f),
		PosVec(200, 30), true, true);
	bdeleteList->SetupText("smart15", "入力された番号を削除", ColorPreset::textObject);
	bdeleteList->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	bdeleteList->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	bdeleteList->SetInnerAnimation(.2f);

	/********** JSON 読込 ***********/

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::setJson, std::ios::binary);

	if (!fs.is_open()) {
		return;
	}

	ss << fs.rdbuf();
	fs.close();

	picojson::value val;
	ss >> val;
	std::string err = picojson::get_last_error();
	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	picojson::object& obj = val.get<picojson::object>();
	picojson::object& jPlayer = obj["Player"].get<picojson::object>();

	ImageChest::CreateImageHandle("Player_play", jPlayer["play"].get<std::string>());
	ImageChest::CreateImageHandle("Player_stop", jPlayer["stop"].get<std::string>());
	ImageChest::CreateImageHandle("Player_noloop", jPlayer["noloop"].get<std::string>());
	ImageChest::CreateImageHandle("Player_oneloop", jPlayer["oneloop"].get<std::string>());
	ImageChest::CreateImageHandle("Player_loop", jPlayer["loop"].get<std::string>());
	ImageChest::CreateImageHandle("Player_shuffle", jPlayer["shuffle"].get<std::string>());

	/******** JSON 読込終了 *********/

	layer.AddObject(bg);

	layer.AddObject(songTitle);
	layer.AddObject(songAuthor);
	layer.AddObject(songHandleName);
	layer.AddObject(nextLabel);
	layer.AddObject(nextTitle);
	layer.AddObject(nextAuthor);
	layer.AddObject(startButton);
	layer.AddObject(loopButton);
	layer.AddObject(playBar);
	layer.AddObject(volumeBar);
	layer.AddObject(lvolume);
	layer.AddObject(playListObject);
	layer.AddObject(ideleteList);
	layer.AddObject(bdeleteList);

	canvases.AddObject(canvas);

	// フォント追加
	fonts.push_back(FontHandle("mplus40", "M PLUS 2", 40, 100));
	fonts.push_back(FontHandle("smart40", "03スマートフォントUI", 40, 15));
	fonts.push_back(FontHandle("smart20", "03スマートフォントUI", 20, 15));
	fonts.push_back(FontHandle("smart15", "03スマートフォントUI", 15, 15));
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

	if (bdeleteList != nullptr) {
		bdeleteList->GetTextObject()->SetPos(bdeleteList->GetPos());
		bdeleteList->GetTextObject()->Move(PosVec(
			(bdeleteList->GetSize().x - bdeleteList->GetTextObject()->GetTextWidth()) / 2.f,
			(bdeleteList->GetSize().y - bdeleteList->GetTextObject()->GetTextHeight()) / 2.f));
		bdeleteList->GetTextObject()->SetForcedArea(
			bdeleteList->GetPos(),
			PosVec(bdeleteList->GetPos().x + bdeleteList->GetSize().x, bdeleteList->GetPos().y + bdeleteList->GetSize().y));

	}

	if (startButton != nullptr) {
		if (startButton->GetMouseSelected()) {
			startButton->SetMouseOff();
			if (!MusicPlayer::GetPlaying())
				MusicPlayer::PlayInList(playStateRotater.GetNowState(), MusicPlayer::GetPlayingIndex(), false);
			else
				MusicPlayer::StopInList();
		}

		if (MusicPlayer::GetPlaying()) {
			startButton->SetImageHandle(ImageChest::GetImageHandle("Player_stop"));
		}
		else {
			startButton->SetImageHandle(ImageChest::GetImageHandle("Player_play"));
		}
	}

	if (loopButton != nullptr) {
		if (loopButton->GetMouseSelected()) {
			loopButton->SetMouseOff();
			playStateRotater.Rotate();
			MusicPlayer::SetPlayingState(playStateRotater.GetNowState());
		}
		PlayState playState = MusicPlayer::GetPlayState();
		switch (playState)
		{
		case PlayState::SIMPLE:
			loopButton->SetImageHandle(ImageChest::GetImageHandle("Player_noloop"));
			break;
		case PlayState::ONE_LOOP:
			loopButton->SetImageHandle(ImageChest::GetImageHandle("Player_oneloop"));
			break;
		case PlayState::ALL_LOOP:
			loopButton->SetImageHandle(ImageChest::GetImageHandle("Player_loop"));
			break;
		case PlayState::RANDOM:
			loopButton->SetImageHandle(ImageChest::GetImageHandle("Player_shuffle"));
			break;
		default:
			break;
		}
	}

	if (nextTitle != nullptr)
		nextTitle->SetText(MusicPlayer::GetPlayNextData().title);
	if (nextAuthor != nullptr)
		nextAuthor->SetText(MusicPlayer::GetPlayNextData().author);

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

	if (volumeBar != nullptr) {
		MusicPlayer::SetVolumeRate(volumeBar->GetValue());
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
		if (bdeleteList->GetMouseSelected() && ideleteList->GetString() != "") {
			bdeleteList->SetMouseOff();
			int deleteIndex;
			try {
				deleteIndex = std::atoi(ideleteList->GetString().c_str());
				MusicPlayer::DeleteFromList(deleteIndex);
				sharingScenes->popupScene->MakeNotice(std::to_string(deleteIndex) + "番をプレイリストから削除しました。");
			}
			catch (std::exception e) {
				sharingScenes->popupScene->MakeNotice("有効な数字を記入してください", "ERROR");
			}
			ideleteList->RemakeHandle();
		}
}

void PlayerScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
