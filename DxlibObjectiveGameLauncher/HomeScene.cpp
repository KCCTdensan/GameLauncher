#include "HomeScene.h"

HomeScene::HomeScene()
	: bg(nullptr), canvas(nullptr)
{}

HomeScene::HomeScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	canvas(nullptr), bg(nullptr),
	works()
{
	canvas = new CanvasObject(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), false);
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	/********** JSON 読込 ***********/

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

	/******** JSON 読込終了 *********/

	int i = 0;
	PosVec startArrangePos(150.f, ApplicationPreference::startScenePos + 100.f);
	PosVec tileSize(350.f, 700.f);
	for (auto& list : lists) {
		works.push_back(nullptr);
		picojson::object& o = list.get<picojson::object>();
		works[i] = new ButtonObject(PosVec(), PosVec(), true, true);
		works[i]->SetPos(PosVec(startArrangePos.x + tileSize.x * (1.f + .15f) * (float)i, startArrangePos.y));
		works[i]->SetSize(tileSize);
		works[i]->SetInnerColor(
			ColorPreset::tileInner,
			ColorPreset::tileHovered,
			ColorPreset::tileClicked,
			ColorPreset::tileSelected);
		works[i]->SetOutlineColor(
			ColorPreset::tileOuter,
			ColorPreset::tileOuterMouse,
			ColorPreset::tileOuterMouse,
			ColorPreset::tileOuterMouse, 6.f);
		works[i]->SetInnerAnimation(.15f);
		works[i]->SetOuterAnimation(.15f);
		works[i]->SetImageAlpha(Color255(0, 220), Color255(0, 25), Color255(0, 255), Color255(0, 255));
		std::string thumbnailName = "Thumb:" + o["GUID"].get<std::string>();
		works[i]->SetTag(o["GUID"].get<std::string>());
		std::string thumbnailPath = o["Directory"].get<std::string>() + o["Thumbnail"].get<std::string>();
		ImageChest::CreateImageHandle(thumbnailName, thumbnailPath);
		int handle = ImageChest::GetImageHandle(thumbnailName);
		PosVec imgSize = ImageChest::GetImageSize(thumbnailName);
		float imgSizeRate;
		works[i]->SetImageHandle(handle);
		if (imgSize.x >= imgSize.y) {
			imgSizeRate = tileSize.x / imgSize.x;
			works[i]->SetImageOffset(PosVec(tileSize.x / 10.f, works[i]->GetSize().y - imgSize.y * imgSizeRate * 1.2f));
		}
		else {
			imgSizeRate = tileSize.x / imgSize.x;
			works[i]->SetImageOffset(PosVec(tileSize.x / 10.f, works[i]->GetSize().y - imgSize.y * imgSizeRate));
		}
		works[i]->SetupText("smart80", o["TitleName"].get<std::string>(), ColorPreset::titleLogo, TextAlign::LEFT);
		works[i]->SetImageSize(PosVec(imgSize.x * imgSizeRate, imgSize.y * imgSizeRate));
		works[i]->SetImageTurnFlag(false, false);
		works[i]->SetImageAngle(std::numbers::pi_v<double> / 12);

		i++;
	}

	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(bg);

	for (auto& item : works) {
		layer.AddObject(item);
		canvas->RegisterChildren(item);
	}

	canvas->SetArea(PosVec(startArrangePos.x + startArrangePos.x + tileSize.x * (1.f + .15f) * (float)lists.size(), -1.f), (startArrangePos.x + tileSize.x * (1.f + .15f)) * 2 / 5000.f);

	canvases.AddObject(canvas);

	// フォント追加
	fonts.push_back(FontHandle("smart80", "03スマートフォントUI", 80, 15));
}

void HomeScene::Collide()
{
	canvases.Collide();
	layer.Collide();

}

void HomeScene::Update()
{
	RegFonts();

	/****************/

	for (auto& item : works) {
		if ((item->GetMouseHit() || item->GetMouseClicked()) || item->GetMouseSelected()) {
			item->GetTextObject()->ChangeValueWithAnimation(&item->GetTextObject()->GetColor(ColorType::INNER)->a, 255, 1.f);
		}
		else {
			item->GetTextObject()->ChangeValueWithAnimation(&item->GetTextObject()->GetColor(ColorType::INNER)->a, 75, 1.f);
		}

		if (item->GetMouseSelected()) {
			item->SetMouseOff();
			std::string id = item->GetTag();
			SceneManager::ChangeScene(item->GetTag(), new WorkScene(sharingScenes, item->GetTag()));
		}
	}

	/****************/

	layer.Update();
	canvases.Update();
}

void HomeScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
