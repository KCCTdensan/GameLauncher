#include "WelcomeScene.h"

WelcomeScene::WelcomeScene()
	: bg(nullptr), canvas(nullptr), icon(nullptr), whatis(nullptr), organization(nullptr), gotoHome(nullptr), openURL(nullptr),
	qrcode(nullptr), imagesCanvas(nullptr), imageBackGround(nullptr)
{
}

WelcomeScene::WelcomeScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	bg(nullptr), canvas(nullptr), icon(nullptr), whatis(nullptr), organization(nullptr), gotoHome(nullptr), openURL(nullptr),
	qrcode(nullptr), imagesCanvas(nullptr), imageBackGround(nullptr)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(bg);

	imageBackGround = new RectangleObject(PosVec(), ApplicationPreference::GetBackgroundSize());
	imageBackGround->SetInnerColor(ColorPreset::backGray);
	imageBackGround->GetColor(ColorType::INNER)->a = 0;
	imageBackGround->SetEnabled(false);

	canvas = new CanvasObject(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true);
	canvas->SetArea(PosVec());
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

	ImageChest::CreateImageHandle(iconName, iconPath);
	ImageChest::CreateImageHandle(qrName, qrPath);
	ImageChest::CreateImageHandle(homeName, homePath);
	ImageChest::CreateImageHandle(orgName, orgPath);
	ImageChest::CreateImageHandle(gotoName, gotoPath);
	ImageChest::CreateImageHandle(whatName, whatPath);

	float maxThumbnailLongLength = 400.f; // 最大幅 どちらかの幅が500になる
	PosVec imageSize = ImageChest::GetImageSize(iconName);
	float imageSizeRate = 0.f;
	if (imageSize.x >= imageSize.y) {
		imageSizeRate = maxThumbnailLongLength / imageSize.x;
	}
	else {
		imageSizeRate = maxThumbnailLongLength / imageSize.y;
	}

	iconPos = PosVec(
		50.f + (imageSize.x >= imageSize.y ? 0.f : (maxThumbnailLongLength - imageSize.x * imageSizeRate) / 2.f),
		ApplicationPreference::startScenePos + 50.f + (imageSize.x >= imageSize.y ? (maxThumbnailLongLength - imageSize.y * imageSizeRate) / 2.f : 0.f));

	iconSize = PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate);

	icon = new ImageObject(
		iconPos, iconSize,
		ImageChest::GetImageHandle(iconName), true, true);
	icon->SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
	icon->SetImageTurnFlag(false, false);

	whatis = new ButtonObject(PosVec(
		50.f, ApplicationPreference::startScenePos + 100.f + maxThumbnailLongLength),
		PosVec(maxThumbnailLongLength, maxThumbnailLongLength), true, true);
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
		PosVec(125.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 50.f),
		PosVec(maxThumbnailLongLength * 2.f, maxThumbnailLongLength), true, true);
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
			125.f + maxThumbnailLongLength,
			ApplicationPreference::startScenePos + 100.f + maxThumbnailLongLength),
		PosVec(800.f, maxThumbnailLongLength), true, true);
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
		PosVec(1000.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 50.f),
		PosVec(maxThumbnailLongLength, maxThumbnailLongLength), true, true);
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
	//openURL->SetupText("mplus100", "HP", Color255("0DE0B9"));
	openURL->SetImageHandle(ImageChest::GetImageHandle(homeName));
	openURL->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	openURL->SetImageTurnFlag(false, false);

	qrcode = new ImageObject(
		PosVec(
			1000.f + maxThumbnailLongLength,
			ApplicationPreference::startScenePos + 100.f + maxThumbnailLongLength),
		PosVec(maxThumbnailLongLength, maxThumbnailLongLength), ImageChest::GetImageHandle(qrName), true, true);
	qrcode->SetInnerColor(
		ColorPreset::tileInner);
	qrcode->SetOutlineColor(
		ColorPreset::navLinksOuter, 3.f);
	qrcode->SetImageSize(PosVec(maxThumbnailLongLength, maxThumbnailLongLength));
	qrcode->SetImageTurnFlag(false, false);

	layer.AddObject(icon);
	layer.AddObject(whatis);
	layer.AddObject(organization);
	layer.AddObject(gotoHome);
	layer.AddObject(openURL);
	layer.AddObject(qrcode);

	//fonts.push_back(FontHandle("mplus180", "M PLUS 2", 180, 100));
	fonts.push_back(FontHandle("mplus100", "M PLUS 2", 100, 100));
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
			SceneManager::ChangeScene("Home", new HomeScene(sharingScenes));
		}

	if (whatis != nullptr)
		if (whatis->GetMouseSelected()) {
			whatis->SetMouseOff();
			SceneManager::ChangeScene("WhatIs", new LauncherScene(sharingScenes));
		}


	layer.Update();
	canvases.Update();
}

void WelcomeScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
