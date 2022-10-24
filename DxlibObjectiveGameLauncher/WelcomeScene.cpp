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

	ImageChest::CreateImageHandle(iconName, iconPath);
	ImageChest::CreateImageHandle(qrName, qrPath);
	ImageChest::CreateImageHandle(homeName, homePath);
	ImageChest::CreateImageHandle(orgName, orgPath);
	ImageChest::CreateImageHandle(gotoName, gotoPath);
	ImageChest::CreateImageHandle(whatName, whatPath);
	ImageChest::CreateImageHandle(musicName, musicPath);

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
		Color255(250,30));
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
			tileStartPos.y + tileMass.y * 3.f),
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

	canvas->RegisterChildren(icon);
	canvas->RegisterChildren(whatis);
	canvas->RegisterChildren(organization);
	canvas->RegisterChildren(gotoHome);
	canvas->RegisterChildren(openURL);
	canvas->RegisterChildren(qrcode);
	canvas->RegisterChildren(jumpToMusic);
	canvas->RegisterChildren(jumpToWorkMan);

	layer.AddObject(icon);
	layer.AddObject(whatis);
	layer.AddObject(organization);
	layer.AddObject(gotoHome);
	layer.AddObject(openURL);
	layer.AddObject(qrcode);
	layer.AddObject(jumpToMusic);
	layer.AddObject(jumpToWorkMan);

	int tileNumY = 3;

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

	layer.Update();
	canvases.Update();
}

void WelcomeScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
