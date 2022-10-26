#include "WelcomeScene.h"

WelcomeScene::WelcomeScene()
	: bg(nullptr), canvas(nullptr), icon(nullptr), whatis(nullptr), organization(nullptr), gotoHome(nullptr), openURL(nullptr),
	qrcode(nullptr), imagesCanvas(nullptr), imageBackGround(nullptr),
	jumpToMusic(nullptr), jumpToWorkMan(nullptr)
{
}

WelcomeScene::WelcomeScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	bg(nullptr), canvas(nullptr), icon(nullptr), whatis(nullptr), organization(nullptr), gotoHome(nullptr), openURL(nullptr),
	qrcode(nullptr), imagesCanvas(nullptr), imageBackGround(nullptr),
	jumpToMusic(nullptr), jumpToWorkMan(nullptr)
{
	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(bg);

	imageBackGround = new RectangleObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	imageBackGround->SetInnerColor(ColorPreset::backGray);
	imageBackGround->GetColor(ColorType::INNER)->a = 0;
	imageBackGround->SetEnabled(false);

	canvas = new CanvasObject(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true);
	canvas->SetInnerColor(ColorPreset::transparent);

	canvas->RegisterChildren(imageBackGround);

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
	picojson::object& welcome = obj["Welcome"].get<picojson::object>();

	this->welcome = welcome;

	/******** JSON 読込終了 *********/

	imagesCanvas = new CanvasObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	imagesCanvas->SetArea(PosVec());
	imagesCanvas->SetInnerColor(ColorPreset::transparent);

	std::string iconName = "Thumb:" + welcome["icon"].get<picojson::object>()["src"].get <std::string>();
	std::string iconPath = welcome["icon"].get<picojson::object>()["src"].get<std::string>();
	std::string qrName = "QR:" + welcome["qrcode"].get<picojson::object>()["src"].get <std::string>();
	std::string qrPath = welcome["qrcode"].get<picojson::object>()["src"].get<std::string>();
	std::string homeName = "HOME:" + welcome["openURL"].get<picojson::object>()["src"].get <std::string>();
	std::string homePath = welcome["openURL"].get<picojson::object>()["src"].get<std::string>();
	std::string whatName = "WHAT:" + welcome["whatis"].get<picojson::object>()["src"].get <std::string>();
	std::string whatPath = welcome["whatis"].get<picojson::object>()["src"].get<std::string>();
	std::string orgName = "ORG:" + welcome["organization"].get<picojson::object>()["src"].get <std::string>();
	std::string orgPath = welcome["organization"].get<picojson::object>()["src"].get<std::string>();
	std::string gotoName = "GOTO:" + welcome["goto-home"].get<picojson::object>()["src"].get <std::string>();
	std::string gotoPath = welcome["goto-home"].get<picojson::object>()["src"].get<std::string>();
	std::string musicName = "GOTO:" + welcome["music-player"].get<picojson::object>()["src"].get <std::string>();
	std::string musicPath = welcome["music-player"].get<picojson::object>()["src"].get<std::string>();
	std::string rankName = "RANK:" + welcome["ranking"].get<picojson::object>()["src"].get <std::string>();
	std::string rankpath = welcome["ranking"].get<picojson::object>()["src"].get<std::string>();
	std::string randomName = "GOTO:" + welcome["random"].get<picojson::object>()["src"].get <std::string>();
	std::string randomPath = welcome["random"].get<picojson::object>()["src"].get<std::string>();

	ImageChest::CreateImageHandle(iconName, iconPath);
	ImageChest::CreateImageHandle(qrName, qrPath);
	ImageChest::CreateImageHandle(homeName, homePath);
	ImageChest::CreateImageHandle(orgName, orgPath);
	ImageChest::CreateImageHandle(gotoName, gotoPath);
	ImageChest::CreateImageHandle(whatName, whatPath);
	ImageChest::CreateImageHandle(musicName, musicPath);
	ImageChest::CreateImageHandle(rankName, rankpath);
	ImageChest::CreateImageHandle(randomName, randomPath);

	const PosVec tileStartPos(175.f, ApplicationPreference::startScenePos + 50.f);
	const PosVec tileSize(400.f, 400.f);
	const PosVec tileGap(0.f, 0.f);
	const PosVec tileMass(tileSize.x + tileGap.x, tileSize.y + tileGap.y);

	float maxThumbnailLongLength = tileSize.x; // 最大幅 どちらかの幅が500になる
	PosVec imageSize = ImageChest::GetImageSize(iconName);
	float imageSizeRate = 0.f;
	if (imageSize.x >= imageSize.y) {
		imageSizeRate = tileSize.x / imageSize.x;
	}
	else {
		imageSizeRate = tileSize.y / imageSize.y;
	}

	iconPos = PosVec(
		tileStartPos.x + (imageSize.x >= imageSize.y ? 0.f : (tileSize.x - imageSize.x * imageSizeRate) / 2.f),
		tileStartPos.y + (imageSize.x >= imageSize.y ? (tileSize.y - imageSize.y * imageSizeRate) / 2.f : 0.f));

	iconSize = PosVec(imageSize.x * tileSize.x, imageSize.y * tileSize.y);

	icon = new ImageObject(
		iconPos, iconSize,
		ImageChest::GetImageHandle(iconName), true, true);
	icon->SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
	icon->SetImageTurnFlag(false, false);

	whatis = new ButtonObject(PosVec(
		tileStartPos.x + tileMass.x * 0.f, tileStartPos.y + tileMass.y * 1.f),
		PosVec(tileSize.x, tileSize.y), true, true);
	whatis->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	whatis->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	whatis->SetInnerAnimation(.2f);
	whatis->SetOuterAnimation(.2f);
	whatis->SetupText("mplus100",
		welcome["whatis"].get<picojson::object>()["text"].get<std::string>(),
		Color255(250, 30));
	whatis->SetImageHandle(ImageChest::GetImageHandle(whatName));
	whatis->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	whatis->SetImageTurnFlag(false, false);

	organization = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x * 2.f,
			tileSize.y), true, true);
	organization->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	organization->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	organization->SetInnerAnimation(.2f);
	organization->SetOuterAnimation(.2f);
	organization->SetupText("mplus100",
		welcome["organization"].get<picojson::object>()["text"].get<std::string>(),
		Color255(250, 30));
	organization->SetImageHandle(ImageChest::GetImageHandle(orgName));
	organization->SetImageSize(PosVec(maxThumbnailLongLength * 2.f, maxThumbnailLongLength));
	organization->SetImageTurnFlag(false, false);

	gotoHome = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 1.f),
		PosVec(
			tileSize.x * 2.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	gotoHome->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	gotoHome->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	gotoHome->SetInnerAnimation(.2f);
	gotoHome->SetOuterAnimation(.2f);
	gotoHome->SetupText("mplus100",
		welcome["goto-home"].get<picojson::object>()["text"].get<std::string>(),
		Color255(250, 30));
	gotoHome->SetImageHandle(ImageChest::GetImageHandle(gotoName));
	gotoHome->SetImageSize(PosVec(maxThumbnailLongLength * 2.f, maxThumbnailLongLength));
	gotoHome->SetImageTurnFlag(false, false);

	openURL = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 3.f,
			tileStartPos.y + tileMass.y * 0.f),
		PosVec(
			tileSize.x + tileGap.x * 0.f,
			tileSize.y + tileGap.y * 0.f), true, true);
	openURL->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	openURL->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	openURL->SetInnerAnimation(.2f);
	openURL->SetOuterAnimation(.2f);
	openURL->SetImageHandle(ImageChest::GetImageHandle(homeName));
	openURL->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	openURL->SetImageTurnFlag(false, false);

	qrcode = new ImageObject(
		PosVec(
			tileStartPos.x + tileMass.x * 3.f,
			tileStartPos.y + tileMass.y * 1.f),
		PosVec(
			maxThumbnailLongLength,
			maxThumbnailLongLength), ImageChest::GetImageHandle(qrName), true, true);
	qrcode->SetInnerColor(
		ColorPreset::tileInner);
	qrcode->SetOutlineColor(
		ColorPreset::navLinksOuter, 3.f);
	qrcode->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	qrcode->SetImageTurnFlag(false, false);

	jumpToMusic = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 0.f,
			tileStartPos.y + tileMass.y * 2.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpToMusic->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpToMusic->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpToMusic->SetupText("mplus100",
		welcome["music-player"].get<picojson::object>()["text"].get<std::string>(),
		Color255(250, 30));
	jumpToMusic->SetInnerAnimation(.2f);
	jumpToMusic->SetOuterAnimation(.2f);
	jumpToMusic->SetImageHandle(ImageChest::GetImageHandle(musicName));
	jumpToMusic->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	jumpToMusic->SetImageTurnFlag(false, false);

	jumpToWorkMan = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 3.f,
			tileStartPos.y + tileMass.y * 5.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpToWorkMan->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpToWorkMan->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpToWorkMan->SetupText("mplus100",
		welcome["work"].get<picojson::object>()["text"].get<std::string>(),
		Color255(50, 30));
	jumpToWorkMan->SetInnerAnimation(.2f);
	jumpToWorkMan->SetOuterAnimation(.2f);

	jumpTorandomPage = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 2.f),
		PosVec(
			tileSize.x * 3.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpTorandomPage->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpTorandomPage->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpTorandomPage->SetupText("mplus100",
		"Random Work",
		Color255(50, 30));
	jumpTorandomPage->SetInnerAnimation(.2f);
	jumpTorandomPage->SetOuterAnimation(.2f);
	jumpTorandomPage->SetImageHandle(ImageChest::GetImageHandle(randomName));
	jumpTorandomPage->SetImageSize(PosVec(maxThumbnailLongLength * 3.f, maxThumbnailLongLength));
	jumpTorandomPage->SetImageTurnFlag(false, false);

	rankButton = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 0.f,
			tileStartPos.y + tileMass.y * 3.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	rankButton->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	rankButton->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	rankButton->SetupText("mplus100",
		welcome["ranking"].get<picojson::object>()["text"].get<std::string>(),
		Color255(50, 30));
	rankButton->SetInnerAnimation(.2f);
	rankButton->SetOuterAnimation(.2f);
	rankButton->SetImageHandle(ImageChest::GetImageHandle(rankName));
	rankButton->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	rankButton->SetImageTurnFlag(false, false);

	jumpToNo1 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 1.f,
			tileStartPos.y + tileMass.y * 3.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpToNo1->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpToNo1->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpToNo1->SetupText("mplus100",
		"No.1",
		Color255(255, 100));
	jumpToNo1->SetInnerAnimation(.2f);
	jumpToNo1->SetOuterAnimation(.2f);
	jumpToNo1->SetImageSize(tileSize);
	jumpToNo1->SetImageTurnFlag(false, false);

	jumpToNo2 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 2.f,
			tileStartPos.y + tileMass.y * 3.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpToNo2->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpToNo2->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpToNo2->SetupText("mplus100",
		"No.2",
		Color255(255, 100));
	jumpToNo2->SetInnerAnimation(.2f);
	jumpToNo2->SetOuterAnimation(.2f);
	jumpToNo2->SetImageSize(tileSize);
	jumpToNo2->SetImageTurnFlag(false, false);

	jumpToNo3 = new ButtonObject(
		PosVec(
			tileStartPos.x + tileMass.x * 3.f,
			tileStartPos.y + tileMass.y * 3.f),
		PosVec(
			tileSize.x * 1.f + tileGap.x * 0.f,
			tileSize.y * 1.f + tileGap.y * 0.f), true, true);
	jumpToNo3->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	jumpToNo3->SetOutlineColor(
		ColorPreset::navLinksOuter,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse,
		ColorPreset::navLinksOuterMouse, 3.f);
	jumpToNo3->SetupText("mplus100",
		"No.3",
		Color255(255, 100));
	jumpToNo3->SetInnerAnimation(.2f);
	jumpToNo3->SetOuterAnimation(.2f);
	jumpToNo3->SetImageSize(tileSize);
	jumpToNo3->SetImageTurnFlag(false, false);


	canvas->RegisterChildren(icon);
	canvas->RegisterChildren(whatis);
	canvas->RegisterChildren(organization);
	canvas->RegisterChildren(gotoHome);
	canvas->RegisterChildren(openURL);
	canvas->RegisterChildren(qrcode);
	canvas->RegisterChildren(jumpToMusic);
	canvas->RegisterChildren(jumpToWorkMan);
	canvas->RegisterChildren(jumpTorandomPage);
	canvas->RegisterChildren(rankButton);
	canvas->RegisterChildren(jumpToNo1);
	canvas->RegisterChildren(jumpToNo2);
	canvas->RegisterChildren(jumpToNo3);

	layer.AddObject(icon);
	layer.AddObject(whatis);
	layer.AddObject(organization);
	layer.AddObject(gotoHome);
	layer.AddObject(openURL);
	layer.AddObject(qrcode);
	layer.AddObject(jumpToMusic);
	layer.AddObject(jumpToWorkMan);
	layer.AddObject(jumpTorandomPage);
	layer.AddObject(rankButton);
	layer.AddObject(jumpToNo1);
	layer.AddObject(jumpToNo2);
	layer.AddObject(jumpToNo3);

	int tileNumY = 5;

	canvas->SetArea(PosVec(
		ApplicationPreference::GetBackgroundSize().x,
		ApplicationPreference::startScenePos + tileSize.y * (float)tileNumY),
		tileSize.y / ((float)tileNumY * tileSize.y) / 2.f
	);
	canvases.AddObject(canvas);

	//fonts.push_back(FontHandle("mplus180", "M PLUS 2", 180, 100));
	fonts.push_back(FontHandle("mplus100", "M PLUS 2", 100, 100));
	fonts.push_back(FontHandle("mplus25", "M PLUS 2", 25, 100));
}

void WelcomeScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void WelcomeScene::Update()
{
	RegFonts();

	if (openURL != nullptr)
		if (openURL->GetMouseSelected()) {
			openURL->SetMouseOff();
			ShellExecute(GetMainWindowHandle(), "open", welcome["openURL"].get<picojson::object>()["url"].get<std::string>().c_str(), NULL, NULL, SW_SHOWNORMAL);
		}

	if (gotoHome != nullptr)
		if (gotoHome->GetMouseSelected()) {
			gotoHome->SetMouseOff();
			SceneManager::ChangeScene("Home", new HomeScene(sharingScenes), false, false);
		}

	if (whatis != nullptr)
		if (whatis->GetMouseSelected()) {
			whatis->SetMouseOff();
			SceneManager::ChangeScene("WhatIs", new LauncherScene(sharingScenes), false, true);
		}

	if (jumpToMusic != nullptr)
		if (jumpToMusic->GetMouseSelected()) {
			jumpToMusic->SetMouseOff();
			SceneManager::ChangeScene("Music Player", new PlayerScene(sharingScenes), false, false);
		}

	if (jumpToWorkMan != nullptr)
		if (jumpToWorkMan->GetMouseSelected()) {
			jumpToWorkMan->SetMouseOff();
			SceneManager::ChangeScene("Work Register", new WorkRegisterScene(sharingScenes));
		}

	if (jumpTorandomPage != nullptr)
		if (jumpTorandomPage->GetMouseSelected()) {
			jumpTorandomPage->SetMouseOff();
			std::random_device rnd;

			/********** JSON 読込 ***********/

			ExePath exePath;
			(void)_chdir(exePath.GetPath());

			std::stringstream ss;
			std::ifstream fs;
			fs.open(ApplicationPreference::worksJson, std::ios::binary);

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

			std::string cGUID = lists[rnd() % lists.size()].get<picojson::object>()["GUID"].get<std::string>();
			SceneManager::ChangeScene(cGUID, new WorkScene(sharingScenes, cGUID), false, true);

		}

	if (jumpToNo1 != nullptr && jumpToNo2 != nullptr && jumpToNo3 != nullptr) {

		/********** JSON 読込 ***********/

		ExePath exePath;
		(void)_chdir(exePath.GetPath());

		std::stringstream ss;
		std::ifstream fs;
		fs.open(ApplicationPreference::analyticsJson, std::ios::binary);

		if (!fs.is_open()) {
			return;
		}

		ss << fs.rdbuf();
		fs.close();

		picojson::value aval;
		ss >> aval;
		std::string err = picojson::get_last_error();
		if (!err.empty()) {
			std::cerr << err << std::endl;
			return;
		}

		picojson::object& aobj = aval.get<picojson::object>();
		picojson::array& alists = aobj["Lists"].get<picojson::array>();

		std::vector<std::pair<int, std::string>> v;

		// ソート
		for (auto& item : alists) {
			v.push_back({ (int)item.get<picojson::object>()["LaunchedTimes"].get<double>(), item.get<picojson::object>()["GUID"].get<std::string>() });
		}
		std::sort(v.rbegin(), v.rend());

		/********** JSON 読込 ***********/

		(void)_chdir(exePath.GetPath());

		fs.open(ApplicationPreference::worksJson, std::ios::binary);

		if (!fs.is_open()) {
			return;
		}

		ss << fs.rdbuf();
		fs.close();

		picojson::value val;
		ss >> val;
		err = picojson::get_last_error();
		if (!err.empty()) {
			std::cerr << err << std::endl;
			return;
		}

		picojson::object& obj = val.get<picojson::object>();
		picojson::array& lists = obj["Lists"].get<picojson::array>();

		int rankMax = 3;
		if (alists.size() < rankMax) rankMax = alists.size();

		if (rankMax < 3) {
			jumpToNo3->SetEnabled(false);
			if (rankMax < 2) {
				jumpToNo2->SetEnabled(false);
					if (rankMax < 1) {
						jumpToNo1->SetEnabled(false);
					}else jumpToNo1->SetEnabled(true);
			}else jumpToNo1->SetEnabled(true);
		}else jumpToNo1->SetEnabled(true);

		for (int i = 0; i < rankMax; i++) {
			ButtonObject* button = nullptr;
			if (i == 0) {
				button = jumpToNo1;
			}
			else if (i == 1) {
				button = jumpToNo2;
			}
			else if (i == 2) {
				button = jumpToNo3;
			}
			for (int j = 0; j < lists.size(); j++) {
				if (v[i].second == lists[j].get<picojson::object>()["GUID"].get<std::string>()) {
					if (button->GetTag() != v[i].second) {

						ExePath exePath;
						(void)_chdir(exePath.GetPath());
						std::string iconName = "Ranking:" + std::to_string(i);
						std::string iconPath = lists[j].get<picojson::object>()["Thumbnail"].get<std::string>();

						ImageChest::DeleteImageHandle(iconName);
						ImageChest::CreateImageHandle(iconName, iconPath);

						button->SetImageHandle(ImageChest::GetImageHandle(iconName));
						button->SetTag(v[i].second);
					}
					break;

				}

			}
			
			if (jumpToNo1->GetMouseSelected()) {
				jumpToNo1->SetMouseOff();
				SceneManager::ChangeScene(jumpToNo1->GetTag(), new WorkScene(sharingScenes, jumpToNo1->GetTag()), false, true);
			}
			if (jumpToNo2->GetMouseSelected()) {
				jumpToNo2->SetMouseOff();
				SceneManager::ChangeScene(jumpToNo2->GetTag(), new WorkScene(sharingScenes, jumpToNo2->GetTag()), false, true);
			}
			if (jumpToNo3->GetMouseSelected()) {
				jumpToNo3->SetMouseOff();
				SceneManager::ChangeScene(jumpToNo3->GetTag(), new WorkScene(sharingScenes, jumpToNo3->GetTag()), false, true);
			}
		}



	}

	layer.Update();
	canvases.Update();
}

void WelcomeScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
