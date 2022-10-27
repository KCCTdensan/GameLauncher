#include "LauncherScene.h"
#include "Header.h"
#include "PopupScene.h"

LauncherScene::LauncherScene()
	: descriptionCanvas(nullptr), thumbnailCanvas(nullptr),
	canvas(nullptr), bg(nullptr),
	thumbnail(nullptr), category(nullptr), title(nullptr), author(nullptr), guidText(nullptr), description(nullptr), descriptionLines(),
	launch(nullptr),
	imagesCanvas(nullptr), isBigCanvas(nullptr), isBigImage(nullptr), isBigPos(nullptr), isBigSize(nullptr), photoGalleryText(nullptr),
	imageBackGround(nullptr)
{
}

LauncherScene::LauncherScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	canvas(nullptr), bg(nullptr),
	descriptionCanvas(nullptr), thumbnailCanvas(nullptr),
	thumbnail(nullptr), category(nullptr), title(nullptr), author(nullptr), guidText(nullptr), description(nullptr), descriptionLines(),
	launch(nullptr),
	imagesCanvas(nullptr), isBigCanvas(nullptr), isBigImage(nullptr), isBigPos(nullptr), isBigSize(nullptr), photoGalleryText(nullptr),
	imageBackGround(nullptr)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(bg);

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
	picojson::object& welcome = obj["Launcher"].get<picojson::object>();

	/******** JSON 読込終了 *********/

	this->obj = welcome; // 保存

	UUIDGenerator uuidGenarator;
	std::string iuuid = uuidGenarator.GetGUID();

	guid = this->obj["GUID"].get<std::string>();

	std::string thumbnailName = iuuid + "[work]Thumb:" + this->obj["GUID"].get<std::string>();
	std::string thumbnailPath = this->obj["Thumbnail"].get<std::string>();

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	char cwd[512];
	// ディレクトリ取得
	int returnId;
	(void)_getcwd(cwd, 512);
	// ファイル直下まで移動
	returnId = _chdir(this->obj["Directory"].get<std::string>().c_str());

	StringConvert stringConvert;

	std::wstring fullpath = stringConvert.ConvertString(this->obj["Thumbnail"].get<std::string>());
	int path_i = (int)fullpath.find_last_of(L"\\");
	std::wstring pathname = fullpath.substr(0, (size_t)(path_i + 1));

	(void)_chdir(stringConvert.ConvertString(pathname).c_str());

	ImageChest::CreateImageHandle(thumbnailName, thumbnailPath);
	handleNames.push_back(thumbnailName);
	float maxThumbnailLongLength = 500.f; // 最大幅 どちらかの幅が500になる
	PosVec imageSize = ImageChest::GetImageSize(thumbnailName);
	float imageSizeRate = 0.f;
	if (imageSize.x >= imageSize.y) {
		imageSizeRate = maxThumbnailLongLength / imageSize.x;
	}
	else {
		imageSizeRate = maxThumbnailLongLength / imageSize.y;
	}

	thumbnailPos = PosVec(
		50.f + (imageSize.x >= imageSize.y ? 0.f : (maxThumbnailLongLength - imageSize.x * imageSizeRate) / 2.f),
		ApplicationPreference::startScenePos + 50.f + (imageSize.x >= imageSize.y ? (maxThumbnailLongLength - imageSize.y * imageSizeRate) / 2.f : 0.f));

	thumbnailSize = PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate);

	thumbnail = new ImageObject(
		thumbnailPos, thumbnailSize,
		ImageChest::GetImageHandle(thumbnailName), true, true);
	thumbnail->SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
	thumbnail->SetImageTurnFlag(false, false);
	thumbnail->SetOutlineColor(ColorPreset::tileOuterMouse, 3.f);

	imageBackGround = new RectangleObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	imageBackGround->SetInnerColor(ColorPreset::backGray);
	imageBackGround->GetColor(ColorType::INNER)->a = 0;
	imageBackGround->SetEnabled(false);

	canvas = new CanvasObject(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true);
	canvas->SetArea(PosVec());
	canvas->SetInnerColor(ColorPreset::transparent);

	thumbnailCanvas = new CanvasObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	thumbnailCanvas->SetArea(PosVec());
	thumbnailCanvas->SetInnerColor(ColorPreset::transparent);

	int i = 0;
	float maxImageLongLength = 300.f; // 最大幅 どちらかの幅が300になる

	for (auto& item : this->obj["Images"].get<picojson::array>()) {
		(void)_chdir(exePath.GetPath());

		char cwd[512];
		// ディレクトリ取得
		int returnId;
		(void)_getcwd(cwd, 512);
		// ファイル直下まで移動
		returnId = _chdir(this->obj["Directory"].get<std::string>().c_str());

		StringConvert stringConvert;

		std::wstring fullpath = stringConvert.ConvertString(item.get<picojson::object>()["FilePath"].get<std::string>());
		int path_i = (int)fullpath.find_last_of(L"\\");
		std::wstring pathname = fullpath.substr(0, (size_t)(path_i + 1));

		(void)_chdir(stringConvert.ConvertString(pathname).c_str());

		std::string imageName = iuuid + "Image" + std::to_string(i) + ":" + this->obj["GUID"].get<std::string>();
		std::string imagePath = item.get<picojson::object>()["FilePath"].get<std::string>();

		ImageChest::CreateImageHandle(imageName, imagePath);
		handleNames.push_back(imageName);
		PosVec imageSize = ImageChest::GetImageSize(imageName);
		float imageSizeRate = 0.f;
		if (imageSize.x >= imageSize.y) {
			imageSizeRate = maxImageLongLength / imageSize.x;
		}
		else {
			imageSizeRate = maxImageLongLength / imageSize.y;
		}
		imagesPos.push_back(PosVec(
			350.f + maxThumbnailLongLength + (maxImageLongLength * 1.2f * (float)i) + (imageSize.x >= imageSize.y ? 0.f : (maxImageLongLength - imageSize.x * imageSizeRate) / 2.f),
			ApplicationPreference::startScenePos + 100.f + maxThumbnailLongLength + (imageSize.x >= imageSize.y ? (maxImageLongLength - imageSize.y * imageSizeRate) / 2.f : 0.f)));

		imagesSize.push_back(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
		images.push_back(new ImageObject(
			imagesPos[i], imagesSize[i],
			ImageChest::GetImageHandle(imageName), true, true));
		images[i]->SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
		images[i]->SetImageTurnFlag(false, false);
		images[i]->SetOutlineColor(ColorPreset::tileOuterMouse, 3.f);

		i++;
		(void)_chdir(exePath.GetPath());
		if (i == 3) break; // 3枚までしか考慮しない
	}

	if (i != 0) {
		photoGalleryText = new TextObject(
			PosVec(125.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 100.f + maxThumbnailLongLength), PosVec(),
			"smart50", "Photo\nGallery", ColorPreset::navLinksOuterMouse, TextAlign::LEFT, false);
	}
	else {
		photoGalleryText = new TextObject();
	}

	imagesCanvas = new CanvasObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	imagesCanvas->SetArea(PosVec());
	imagesCanvas->SetInnerColor(ColorPreset::transparent);

	canvas->RegisterChildren(imageBackGround);
	thumbnailCanvas->RegisterChildren(thumbnail);

	// 初期位置 +10
	category = new TextObject(
		PosVec(ApplicationPreference::GetBackgroundSize().x - 20.f, ApplicationPreference::startScenePos + 10.f), PosVec(),
		"smart30", "Category: " + this->obj["Category"].get<std::string>(), ColorPreset::textGray, TextAlign::RIGHT, false);

	// 初期位置 +50
	title = new TextObject(
		PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 50.f), PosVec(),
		"smart50", this->obj["TitleName"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
	title->DeleteNewLine();

	// +100
	author = new TextObject(
		PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 100.f), PosVec(),
		"smart25", this->obj["Author"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
	author->DeleteNewLine();

	// +125
	guidText = new TextObject(
		PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 125.f), PosVec(),
		"smart25", this->obj["GUID"].get<std::string>(), ColorPreset::textGray, TextAlign::LEFT, false);

	// +150
	description = new TextObject(
		PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 150.f), PosVec(),
		"smart30", this->obj["Description"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
	description->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxThumbnailLongLength));

	descriptionCanvas = new CanvasObject(
		PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 150.f),
		PosVec(
			ApplicationPreference::GetBackgroundSize().x - 100.f - maxThumbnailLongLength,
			maxThumbnailLongLength - 100.f), true);
	// 高さ取得
	float textHeight = (float)description->GetTextHeight() * ApplicationPreference::returnTextIndent;
	descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description->GetFontHeight() * 2.f / textHeight);

	descriptionCanvas->SetInnerColor(ColorPreset::transparent);
	descriptionCanvas->RegisterChildren(description);

	descriptionLines.resize(2, nullptr);
	for (auto& item : descriptionLines) {
		item = new LineObject(
			PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 150.f),
			PosVec(75.f + maxThumbnailLongLength + descriptionCanvas->GetSize().x, ApplicationPreference::startScenePos + 150.f));
		layer.AddObject(item);
		item->SetOutlineColor(ColorPreset::navLinksOuterMouse, 2.f);
	}
	descriptionLines[1]->SetPos(PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 150.f + descriptionCanvas->GetSize().y));
	descriptionLines[1]->SetSize(PosVec(75.f + maxThumbnailLongLength + descriptionCanvas->GetSize().x, ApplicationPreference::startScenePos + 150.f + descriptionCanvas->GetSize().y));

	openWeb = new ButtonObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 375.f),
		PosVec(maxThumbnailLongLength, 100.f), true, true);
	openWeb->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	openWeb->SetInnerAnimation(.1f);
	openWeb->SetOutlineColor(ColorPreset::yellowButtonOuter, 3.f);
	openWeb->SetupText("smart30", "Open In Browser", ColorPreset::textObject, TextAlign::LEFT);

	copyGUID = new ButtonObject(
		PosVec(650.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 120.f),
		PosVec(100, 25.f), true, true);
	copyGUID->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	copyGUID->SetInnerAnimation(.1f);
	copyGUID->SetOutlineColor(ColorPreset::yellowButtonOuter, 3.f);
	copyGUID->SetupText("smart20", "COPY", ColorPreset::textObject, TextAlign::LEFT);

	if (this->obj["URL"].get<std::string>() == "") openWeb->SetEnabled(false);

	launch = new ButtonObject(
		PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 200.f),
		PosVec(maxThumbnailLongLength, 150.f), true, true);
	launch->SetInnerColor(
		Color255("#F7D322"),
		Color255("#D8B91E"),
		Color255("#D1B31D"),
		Color255("#F2CF21"));
	launch->SetInnerAnimation(.1f);
	launch->SetOutlineColor(Color255("#EDB142"), 3.f);
	launch->SetupText("smart80", "Start", ColorPreset::textObject, TextAlign::LEFT);
	launch->GetTextObject()->Move(PosVec(
		(maxThumbnailLongLength - launch->GetTextObject()->GetTextWidth()) / 2.f,
		(150.f - launch->GetTextObject()->GetTextHeight()) / 2.f));

	layer.AddObject(imageBackGround);
	layer.AddObject(thumbnail);

	for (auto& item : images) {
		layer.AddObject(item);
		imagesCanvas->RegisterChildren(item);
	}

	layer.AddObject(category);
	layer.AddObject(title);
	layer.AddObject(author);
	layer.AddObject(guidText);
	layer.AddObject(description);
	layer.AddObject(photoGalleryText);
	layer.AddObject(copyGUID);
	layer.AddObject(openWeb);

	layer.AddObject(launch);

	canvases.AddObject(canvas);
	canvases.AddObject(imagesCanvas);
	canvases.AddObject(thumbnailCanvas);
	canvases.AddObject(descriptionCanvas);


	// フォント追加
	fonts.push_back(FontHandle("smart80", "03スマートフォントUI", 80, 15));
	fonts.push_back(FontHandle("smart50", "03スマートフォントUI", 50, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
	fonts.push_back(FontHandle("smart25", "03スマートフォントUI", 25, 15));
	fonts.push_back(FontHandle("smart20", "03スマートフォントUI", 20, 15));
}

LauncherScene::~LauncherScene()
{
	SceneBase::~SceneBase();

	for (auto& item : handleNames) {
		ImageChest::DeleteImageHandle(item);
	}

	SaftyDelete(canvas);	SaftyDelete(bg);
	SaftyDelete(thumbnail); SaftyDelete(category); SaftyDelete(title); SaftyDelete(author); SaftyDelete(guidText);
	SaftyDelete(description); SaftyDelete(photoGalleryText); SaftyDelete(descriptionCanvas);
	SaftyDelete(thumbnailCanvas); SaftyDelete(imagesCanvas); SaftyDelete(launch); SaftyDelete(imageBackGround);

	if (isBigPos == nullptr)
		delete isBigPos;
	if (isBigSize == nullptr)
		delete isBigSize;

	for (auto& item : descriptionLines)
		delete item;
	for (auto& item : images)
		delete item;
}

void LauncherScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void LauncherScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();

	// 高さ取得
	if (descriptionCanvas != nullptr && description != nullptr)
		if ((int)descriptionCanvas->GetArea().y < (int)((float)description->GetTextHeight() * ApplicationPreference::returnTextIndent)) {
			float textHeight = (float)description->GetTextHeight() * ApplicationPreference::returnTextIndent;
			descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description->GetFontHeight() * 2.f / textHeight);
		}

	if (openWeb != nullptr) {
		openWeb->GetTextObject()->SetPos(openWeb->GetPos());
		openWeb->GetTextObject()->Move(PosVec(
			(openWeb->GetSize().x - openWeb->GetTextObject()->GetTextWidth()) / 2.f,
			(openWeb->GetSize().y - openWeb->GetTextObject()->GetTextHeight()) / 2.f));
		openWeb->GetTextObject()->SetForcedArea(
			openWeb->GetPos(),
			PosVec(launch->GetPos().x + launch->GetSize().x, launch->GetPos().y + launch->GetSize().y));
	}

	if (launch != nullptr) {
		launch->GetTextObject()->SetPos(launch->GetPos());
		launch->GetTextObject()->Move(PosVec(
			(launch->GetSize().x - launch->GetTextObject()->GetTextWidth()) / 2.f,
			(launch->GetSize().y - launch->GetTextObject()->GetTextHeight()) / 2.f));
		launch->GetTextObject()->SetForcedArea(
			launch->GetPos(),
			PosVec(launch->GetPos().x + launch->GetSize().x, launch->GetPos().y + launch->GetSize().y));
	}

	if (copyGUID != nullptr) {
		copyGUID->GetTextObject()->SetPos(copyGUID->GetPos());
		copyGUID->GetTextObject()->Move(PosVec(
			(copyGUID->GetSize().x - copyGUID->GetTextObject()->GetTextWidth()) / 2.f,
			(copyGUID->GetSize().y - copyGUID->GetTextObject()->GetTextHeight()) / 2.f));
		copyGUID->GetTextObject()->SetForcedArea(
			copyGUID->GetPos(),
			PosVec(copyGUID->GetPos().x + copyGUID->GetSize().x, copyGUID->GetPos().y + copyGUID->GetSize().y));
	}

	sharingScenes->header->SetSubtitle(this->obj["TitleName"].get<std::string>());

	if (copyGUID != nullptr)
		if (copyGUID->GetMouseSelected()) {
			copyGUID->SetMouseOff();

			if (!::OpenClipboard(GetMainWindowHandle())) {
				sharingScenes->popupScene->MakeNotice("クリップボードを開けませんでした。", "ERROR");
				return;
			}

			if (!::EmptyClipboard()) {
				::CloseClipboard();
				sharingScenes->popupScene->MakeNotice("クリップボードをクリアできませんでした。", "ERROR");
				return;
			}

			HGLOBAL hGlobal = GlobalAlloc(GHND, guid.length() + 1);
			if (!hGlobal) {
				::CloseClipboard();
				sharingScenes->popupScene->MakeNotice("クリップボードにてメモリを確保できませんでした。", "ERROR");
			}
			else {
				LPTSTR p = (LPTSTR)GlobalLock(hGlobal);
				wsprintf(p, guid.c_str());
				GlobalUnlock(hGlobal);

				::SetClipboardData(CF_TEXT, hGlobal);

				::CloseClipboard();
				sharingScenes->popupScene->MakeNotice("クリップボードにコピーしました。");
			}
		}

	if (openWeb != nullptr)
		if (openWeb->GetMouseSelected() && this->obj["URL"].get<std::string>() != "") {
			openWeb->SetMouseOff();

			try {
				ShellExecute(GetMainWindowHandle(), "open", this->obj["URL"].get<std::string>().c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
			catch (std::exception e) {
				// throw
			}
		}

	if (launch != nullptr)
		if (launch->GetMouseSelected() && this->obj["FilePath"].get<std::string>() != "") {

			ExePath exePath;
			(void)_chdir(exePath.GetPath());

			// 押下時の処理をここに
			launch->SetMouseOff();
			char cwd[512];
			// ディレクトリ取得
			int returnId;
			(void)_getcwd(cwd, 512);
			// ファイル直下まで移動
			returnId = _chdir(this->obj["Directory"].get<std::string>().c_str());

			StringConvert stringConvert;

			std::wstring fullpath = stringConvert.ConvertString(this->obj["FilePath"].get<std::string>());
			int path_i = (int)fullpath.find_last_of(L"\\");
			std::wstring pathname = fullpath.substr(0, (size_t)(path_i + 1));

			(void)_chdir(stringConvert.ConvertString(pathname).c_str());

			if (this->obj["Category"].get<std::string>() == ApplicationPreference::musicCategoryName) {
				PlayData playData;
				MusicChest::CreateMusicHandle(this->obj["GUID"].get<std::string>(), this->obj["FilePath"].get<std::string>());

				playData.title = this->obj["TitleName"].get<std::string>();
				playData.author = this->obj["Author"].get<std::string>();
				playData.handle = MusicChest::GetMusicHandle(this->obj["GUID"].get<std::string>());

				if (playData.handle < 0) {
					sharingScenes->popupScene->MakeNotice("ファイルが見つからない、もしくは開けませんでした。", "ERROR");
				}
				else {
					sharingScenes->popupScene->MakeNotice("音声ファイル読み込み完了");
				}

				MusicPlayer::AddToList(playData);

				// 元のディレクトリに戻す
				returnId = _chdir(cwd);
				(void)_chdir(exePath.GetPath());

				SceneManager::ChangeScene("Music Player", new PlayerScene(sharingScenes));
			}
			else {

				const char* ext = std::strrchr(this->obj["FilePath"].get<std::string>().c_str(), '.');

				bool normalLaunch = true;

				if (ext) {
					std::string extNoticeText = "拡張子を取得しました。: ";
					extNoticeText += ext;
					sharingScenes->popupScene->MakeNotice(extNoticeText);
					std::string extname = ext;
					if (
						extname == ".wav" || extname == ".WAV" ||
						extname == ".mp3" || extname == ".MP3" ||
						extname == ".ogg" || extname == ".Ogg" || extname == "Ogg" ||
						extname == ".opus" || extname == ".OPUS") {
						sharingScenes->popupScene->MakeNotice("拡張子が音楽ファイルであったため音楽プレイヤーで読込を開始します。");
						normalLaunch = false;

						PlayData playData;
						MusicChest::CreateMusicHandle(this->obj["GUID"].get<std::string>(), this->obj["FilePath"].get<std::string>());

						playData.title = this->obj["TitleName"].get<std::string>();
						playData.author = this->obj["Author"].get<std::string>();
						playData.handle = MusicChest::GetMusicHandle(this->obj["GUID"].get<std::string>());

						if (playData.handle < 0) {
							sharingScenes->popupScene->MakeNotice("ファイルが見つからない、もしくは開けませんでした。");
						}
						else {
							sharingScenes->popupScene->MakeNotice("音声ファイル読み込み完了");
						}

						MusicPlayer::AddToList(playData);

						// 元のディレクトリに戻す
						returnId = _chdir(cwd);
						(void)_chdir(exePath.GetPath());

						SceneManager::ChangeScene("Music Player", new PlayerScene(sharingScenes));
					}
				}
				else {
					sharingScenes->popupScene->MakeNotice("拡張子のないファイルです。");
				}
				if (normalLaunch) {
					StringConvert stringConvert;

					std::string path = this->obj["FilePath"].get<std::string>().c_str();
					std::wstring wpath = stringConvert.ConvertString(path);

					size_t posPath = wpath.rfind(L"\\");
					if (posPath != std::wstring::npos) {
						wpath = wpath.substr(posPath + 1, wpath.size() - posPath - 1);
					}

					posPath = wpath.rfind(L"/");
					if (posPath != std::wstring::npos) {
						wpath = wpath.substr(posPath + 1, wpath.size() - posPath - 1);
					}

					// 実行
					ShellExecute(GetMainWindowHandle(), "open", stringConvert.ConvertString(wpath).c_str(), NULL, NULL, SW_SHOWNORMAL);
					switch (GetLastError())
					{
					case ERROR_FILE_NOT_FOUND:
						sharingScenes->popupScene->MakeNotice("ファイルが見つかりませんでした。", "ERROR");
						break;
					case ERROR_PATH_NOT_FOUND:
						sharingScenes->popupScene->MakeNotice("パスが見つかりませんでした。", "ERROR");
						break;
					case ERROR_ACCESS_DENIED:
						sharingScenes->popupScene->MakeNotice("アクセス拒否されました。", "ERROR");
						break;
					case ERROR_NOT_ENOUGH_MEMORY:
						sharingScenes->popupScene->MakeNotice("メモリ不足です。", "ERROR");
						break;
					default:
						break;
					}
				}
			}
			// 元のディレクトリに戻す
			returnId = _chdir(cwd);

			(void)_chdir(exePath.GetPath());

			/********** JSON 読込 ***********/

			std::stringstream ss;
			std::ifstream fs;
			fs.open(ApplicationPreference::analyticsJson, std::ios::binary);

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
			picojson::array& lists = obj["Lists"].get<picojson::array>();

			picojson::object* newGUIDSave = new picojson::object;
			picojson::object* newTime = new picojson::object;
			picojson::array* newTimeList = new picojson::array;

			bool isExisting = false;

			for (auto& item : lists) {
				if (item.get<picojson::object>()["GUID"].get<std::string>() == guid) {
					isExisting = true;

					item.get<picojson::object>()["LaunchedTimes"].get<double>() += 1.;

					picojson::array& time = item.get<picojson::object>()["Time"].get<picojson::array>();
					newTime->insert(std::make_pair("Time", picojson::value(static_cast<double>(::time(nullptr)))));
					time.push_back(picojson::value(*newTime));

					break;
				}
			}

			if (!isExisting) {
				newGUIDSave->insert(std::make_pair("GUID", picojson::value(guid.c_str())));
				newGUIDSave->insert(std::make_pair("LaunchedTimes", picojson::value(1.)));

				newTime->insert(std::make_pair("Time", picojson::value(static_cast<double>(::time(nullptr)))));
				newTimeList->push_back(picojson::value(*newTime));
				newGUIDSave->insert(std::make_pair("Time", picojson::value(*newTimeList)));

				lists.push_back(picojson::value(*newGUIDSave));
			}

			std::ofstream ofs;
			ofs.open(ApplicationPreference::analyticsJson, std::ios::binary);

			ofs << picojson::value(obj).serialize(true) << std::endl;
			ofs.close();
			sharingScenes->popupScene->MakeNotice(ApplicationPreference::analyticsJson + "に保存しました。");
		}

	if (thumbnail != nullptr)
		if (thumbnail->GetMouseSelected() && !imageBackGround->SetEnabled()) {
			thumbnail->SetMouseOff();
			isBigImage = thumbnail;
			isBigCanvas = thumbnailCanvas;
			isBigPos = &thumbnailPos;
			isBigSize = &thumbnailSize;

			// 最大を800にする;
			PosVec imageSize;
			GetGraphSizeF(thumbnail->GetImageHandle(), &imageSize.x, &imageSize.y);
			float imageSizeRate = 0.f;
			if (imageSize.x >= imageSize.y) {
				imageSizeRate = maxImageLongLengthOnBig / imageSize.x;
			}
			else {
				imageSizeRate = maxImageLongLengthOnBig / imageSize.y;
			}

			PosVec thumbnailPos = PosVec(
				(ApplicationPreference::GetBackgroundSize().x - maxImageLongLengthOnBig) / 2 + (imageSize.x >= imageSize.y ? 0.f : (maxImageLongLengthOnBig - imageSize.x * imageSizeRate) / 2.f),
				ApplicationPreference::startScenePos + (ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos - maxImageLongLengthOnBig) / 2 + (imageSize.x >= imageSize.y ? (maxImageLongLengthOnBig - imageSize.y * imageSizeRate) / 2.f : 0.f));

			PosVec thumbnailSize = PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate);

			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::POS)->x, thumbnailPos.x, zoomFrame);
			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::POS)->y, thumbnailPos.y, zoomFrame);
			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::SIZE)->x, thumbnailSize.x, zoomFrame);
			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::SIZE)->y, thumbnailSize.y, zoomFrame);
			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::IMAGE_SIZE)->x, thumbnailSize.x, zoomFrame);
			thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::IMAGE_SIZE)->y, thumbnailSize.y, zoomFrame);
			imageBackGround->SetEnabled(true);
			imageBackGround->ChangeValueWithAnimation(
				&imageBackGround->GetColor(ColorType::INNER)->a, ColorPreset::backGray.a, zoomFrame);
			canvases.SetTopLayer(canvas);
			canvases.SetTopLayer(thumbnailCanvas);
			layer.SetTopLayer(imageBackGround);
			layer.SetTopLayer(thumbnail);
		}
	int i = 0;
	for (auto& item : images) {
		if (item != nullptr)
			if (item->GetMouseSelected() && !imageBackGround->SetEnabled()) {
				item->SetMouseOff();
				isBigImage = item;
				isBigCanvas = imagesCanvas;
				isBigPos = &imagesPos[i];
				isBigSize = &imagesSize[i];

				// 最大を800にする;
				PosVec imageSize;
				GetGraphSizeF(item->GetImageHandle(), &imageSize.x, &imageSize.y);
				float imageSizeRate = 0.f;
				if (imageSize.x >= imageSize.y) {
					imageSizeRate = maxImageLongLengthOnBig / imageSize.x;
				}
				else {
					imageSizeRate = maxImageLongLengthOnBig / imageSize.y;
				}

				PosVec itemPos = PosVec(
					(ApplicationPreference::GetBackgroundSize().x - maxImageLongLengthOnBig) / 2 + (imageSize.x >= imageSize.y ? 0.f : (maxImageLongLengthOnBig - imageSize.x * imageSizeRate) / 2.f),
					ApplicationPreference::startScenePos + (ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos - maxImageLongLengthOnBig) / 2 + (imageSize.x >= imageSize.y ? (maxImageLongLengthOnBig - imageSize.y * imageSizeRate) / 2.f : 0.f));

				PosVec itemSize = PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate);

				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::POS)->x, itemPos.x, zoomFrame);
				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::POS)->y, itemPos.y, zoomFrame);
				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::SIZE)->x, itemSize.x, zoomFrame);
				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::SIZE)->y, itemSize.y, zoomFrame);
				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::IMAGE_SIZE)->x, itemSize.x, zoomFrame);
				item->ChangeValueWithAnimation(&item->GetVectorPointer(VectorType::IMAGE_SIZE)->y, itemSize.y, zoomFrame);
				imageBackGround->SetEnabled(true);
				imageBackGround->ChangeValueWithAnimation(
					&imageBackGround->GetColor(ColorType::INNER)->a, ColorPreset::backGray.a, zoomFrame);
				canvases.SetTopLayer(canvas);
				canvases.SetTopLayer(imagesCanvas);
				layer.SetTopLayer(imageBackGround);
				layer.SetTopLayer(item);
			}
		i++;
	}

	if (imageBackGround != nullptr)
		if (imageBackGround->SetEnabled() && imageBackGround->GetMouseSelected()) {
			imageBackGround->SetMouseOff();
			imageBackGround->SetEnabled(false);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::POS)->x, isBigPos->x, zoomFrame);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::POS)->y, isBigPos->y, zoomFrame);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::SIZE)->x, isBigSize->x, zoomFrame);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::SIZE)->y, isBigSize->y, zoomFrame);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::IMAGE_SIZE)->x, isBigSize->x, zoomFrame);
			isBigImage->ChangeValueWithAnimation(&isBigImage->GetVectorPointer(VectorType::IMAGE_SIZE)->y, isBigSize->y, zoomFrame);
			imageBackGround->ChangeValueWithAnimation(
				&imageBackGround->GetColor(ColorType::INNER)->a, 0, zoomFrame);
			canvases.SetButtomLayer(isBigCanvas);
			canvases.SetButtomLayer(canvas);
		}
}

void LauncherScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
