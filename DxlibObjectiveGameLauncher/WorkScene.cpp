#include "WorkScene.h"
#include "Header.h"

WorkScene::WorkScene()
	: descriptionCanvas(nullptr)
{}

WorkScene::WorkScene(SharingScenes* _sharingScenes, std::string workGuid)
	: SceneBase(_sharingScenes), guid(workGuid),
	canvas(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true),
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	descriptionCanvas(nullptr)
{
	bg.SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)
	layer.AddObject(&bg);

	/********** JSON 読込 ***********/

	std::stringstream ss;
	std::ifstream fs;
	fs.open("data.json", std::ios::binary);

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
	for (auto& list : lists) {
		if (list.get<picojson::object>()["GUID"].get<std::string>() == guid) break;
		i++;
	}

	if ((int)lists.size() == i) { // 未発見時の処理
		//printfDx("Not Found : %s\n", guid.c_str());
	}
	else { // 発見時の処理
		//printfDx("%s\n", lists[i].get<picojson::object>()["GUID"].get<std::string>().c_str());
		this->obj = lists[i].get<picojson::object>(); // 保存

		std::string thumbnailName = "Thumb:" + this->obj["GUID"].get<std::string>();
		std::string thumbnailPath = this->obj["Directory"].get<std::string>() + this->obj["Thumbnail"].get<std::string>();

		ImageChest::CreateImageHandle(thumbnailName, thumbnailPath);
		int handle = ImageChest::GetImageHandle(thumbnailName);
		float maxImageLongLength = 500.f; // 最大幅 どちらかの幅が500になる
		PosVec imageSize = ImageChest::GetImageSize(thumbnailName);
		float imageSizeRate = 0.f;
		if (imageSize.x >= imageSize.y) {
			imageSizeRate = maxImageLongLength / imageSize.x;
		}
		else {
			imageSizeRate = maxImageLongLength / imageSize.y;
		}

		thumbnail = ImageObject(
			PosVec(
				50.f + (imageSize.x >= imageSize.y ? 0.f : (maxImageLongLength - imageSize.x * imageSizeRate) / 2.f),
				ApplicationPreference::startScenePos + 50.f + (imageSize.x >= imageSize.y ? (maxImageLongLength - imageSize.y * imageSizeRate) / 2.f : 0.f)),
			PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate),
			ImageChest::GetImageHandle(thumbnailName), true, true);
		thumbnail.SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
		thumbnail.SetImageTurnFlag(false, false);
		thumbnail.SetOutlineColor(ColorPreset::tileOuterMouse, 3.f);

		title = TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 50.f), PosVec(),
			"smart50", this->obj["TitleName"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		title.SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		description = TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f), PosVec(),
			"smart30", this->obj["Description"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		description.SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));
	
		descriptionCanvas = new CanvasObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f),
			PosVec(
				ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength,
				maxImageLongLength - 100.f), true);
		// 高さ取得
		float textHeight = (float)description.GetTextHeight() * 1.15f;
		descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description.GetFontHeight() / textHeight);

		descriptionCanvas->SetInnerColor(Color255(0,0));
		descriptionCanvas->RegisterChildren(&description);

		canvases.AddObject(descriptionCanvas);
	}

	layer.AddObject(&thumbnail);
	layer.AddObject(&title);
	layer.AddObject(&description);

	// フォント追加
	fonts.push_back(FontHandle("smart50", "03スマートフォントUI", 50, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
}

void WorkScene::Collide()
{
	canvases.Collide();
	layer.Collide();

	/****************/

	/****************/
}

void WorkScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();

	// 高さ取得
	if ((int)descriptionCanvas->GetArea().y < (int)((float)description.GetTextHeight() * 1.15f)) {
		float textHeight = (float)description.GetTextHeight() * 1.15f;
		descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description.GetFontHeight() / textHeight);
	}

	sharingScenes->header->SetSubtitle(this->obj["TitleName"].get<std::string>());
}

void WorkScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
