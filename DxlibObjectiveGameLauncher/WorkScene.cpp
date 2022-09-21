#include "WorkScene.h"
#include "Header.h"

WorkScene::WorkScene()
	: descriptionCanvas(nullptr), thumbnailCanvas(nullptr),
	thumbnail(nullptr), category(nullptr), title(nullptr), author(nullptr), guidText(nullptr), description(nullptr), descriptionLines(),
	launch(nullptr),
	thumbnailBackGround(nullptr)
{}

WorkScene::WorkScene(SharingScenes* _sharingScenes, std::string workGuid)
	: SceneBase(_sharingScenes), guid(workGuid),
	canvas(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true),
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	descriptionCanvas(nullptr), thumbnailCanvas(nullptr),
	thumbnail(nullptr), category(nullptr), title(nullptr), author(nullptr), guidText(nullptr), description(nullptr), descriptionLines(),
	launch(nullptr),
	thumbnailBackGround(nullptr)
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

		thumbnailPos = PosVec(
			50.f + (imageSize.x >= imageSize.y ? 0.f : (maxImageLongLength - imageSize.x * imageSizeRate) / 2.f),
			ApplicationPreference::startScenePos + 50.f + (imageSize.x >= imageSize.y ? (maxImageLongLength - imageSize.y * imageSizeRate) / 2.f : 0.f));

		thumbnailSize = PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate);

		thumbnail = new ImageObject(
			thumbnailPos, thumbnailSize,
			ImageChest::GetImageHandle(thumbnailName), true, true);
		thumbnail->SetImageSize(PosVec(imageSize.x * imageSizeRate, imageSize.y * imageSizeRate));
		thumbnail->SetImageTurnFlag(false, false);
		thumbnail->SetOutlineColor(ColorPreset::tileOuterMouse, 3.f);

		thumbnailBackGround = new RectangleObject(PosVec(), ApplicationPreference::GetBackgroundSize());
		//thumbnailBackGround->SetInnerColor(ColorPreset::backGray);
		thumbnailBackGround->GetColor(ColorType::INNER)->a = 0;
		thumbnailBackGround->SetEnabled(false);

		thumbnailCanvas = new CanvasObject(PosVec(), ApplicationPreference::GetBackgroundSize());
		thumbnailCanvas->SetArea(PosVec());
		thumbnailCanvas->SetInnerColor(ColorPreset::transparent);

		thumbnailCanvas->RegisterChildren(thumbnailBackGround);
		thumbnailCanvas->RegisterChildren(thumbnail);

		// 初期位置 +10
		category = new TextObject(
			PosVec(ApplicationPreference::GetBackgroundSize().x - 20.f, ApplicationPreference::startScenePos + 10.f), PosVec(),
			"smart30", "Category: " + this->obj["Category"].get<std::string>(), ColorPreset::textGray, TextAlign::RIGHT, false);
		//category->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// 初期位置 +50
		title = new TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 50.f), PosVec(),
			"smart50", this->obj["TitleName"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		//title->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// +100
		author = new TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 100.f), PosVec(),
			"smart25", this->obj["Author"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		//author->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// +125
		guidText = new TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 125.f), PosVec(),
			"smart25", this->obj["GUID"].get<std::string>(), ColorPreset::textGray, TextAlign::LEFT, false);
		//guidText->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// +150
		description = new TextObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f), PosVec(),
			"smart30", this->obj["Description"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		description->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		descriptionCanvas = new CanvasObject(
			PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f),
			PosVec(
				ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength,
				maxImageLongLength - 100.f), true);
		// 高さ取得
		float textHeight = (float)description->GetTextHeight() * ApplicationPreference::returnTextIndent;
		descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description->GetFontHeight() / textHeight);

		descriptionCanvas->SetInnerColor(ColorPreset::transparent);
		descriptionCanvas->RegisterChildren(description);

		descriptionLines.resize(2, nullptr);
		for (auto& item : descriptionLines) {
			item = new LineObject(
				PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f),
				PosVec(75.f + maxImageLongLength + descriptionCanvas->GetSize().x, ApplicationPreference::startScenePos + 150.f));
			layer.AddObject(item);
			item->SetOutlineColor(ColorPreset::navLinksOuterMouse, 2.f);
		}
		descriptionLines[1]->SetPos(PosVec(75.f + maxImageLongLength, ApplicationPreference::startScenePos + 150.f + descriptionCanvas->GetSize().y));
		descriptionLines[1]->SetSize(PosVec(75.f + maxImageLongLength + descriptionCanvas->GetSize().x, ApplicationPreference::startScenePos + 150.f + descriptionCanvas->GetSize().y));

		launch = new ButtonObject(
			PosVec(50.f, ApplicationPreference::GetBackgroundSize().y - 200.f),
			PosVec(maxImageLongLength, 150.f), true, true);
		launch->SetInnerColor(
			Color255("#F7D322"),
			Color255("#D8B91E"),
			Color255("#D1B31D"),
			Color255("#F2CF21"));
		launch->SetInnerAnimation(.1f);
		launch->SetOutlineColor(Color255("#EDB142"), 3.f);

		layer.AddObject(thumbnailBackGround);
		layer.AddObject(thumbnail);
		layer.AddObject(category);
		layer.AddObject(title);
		layer.AddObject(author);
		layer.AddObject(guidText);
		layer.AddObject(description);

		layer.AddObject(launch);

		canvases.AddObject(thumbnailCanvas);
		canvases.AddObject(descriptionCanvas);
	}

	// フォント追加
	fonts.push_back(FontHandle("smart50", "03スマートフォントUI", 50, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
	fonts.push_back(FontHandle("smart25", "03スマートフォントUI", 25, 15));
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
	if (descriptionCanvas != nullptr && description != nullptr)
		if ((int)descriptionCanvas->GetArea().y < (int)((float)description->GetTextHeight() * ApplicationPreference::returnTextIndent)) {
			float textHeight = (float)description->GetTextHeight() * ApplicationPreference::returnTextIndent;
			descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description->GetFontHeight() / textHeight);
		}

	sharingScenes->header->SetSubtitle(this->obj["TitleName"].get<std::string>());

	if (launch != nullptr)
		if (launch->GetMouseSelected()) {
			// 押下時の処理をここに
			launch->SetMouseOff();
		}

	if (thumbnail != nullptr)
		if (thumbnail->GetMouseSelected() && !thumbnailBackGround->SetEnabled()) {
			thumbnail->SetMouseOff();

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
			thumbnailBackGround->SetEnabled(true);
			thumbnailBackGround->ChangeValueWithAnimation(
				&thumbnailBackGround->GetColor(ColorType::INNER)->a, ColorPreset::backGray.a, zoomFrame);
			canvases.SetTopLayer(thumbnailCanvas);
			layer.SetTopLayer(thumbnailBackGround);
			layer.SetTopLayer(thumbnail);
		}
		else {
			if (thumbnailBackGround->GetMouseSelected()) {
				thumbnailBackGround->SetMouseOff();
				thumbnailBackGround->SetEnabled(false);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::POS)->x, thumbnailPos.x, zoomFrame);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::POS)->y, thumbnailPos.y, zoomFrame);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::SIZE)->x, thumbnailSize.x, zoomFrame);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::SIZE)->y, thumbnailSize.y, zoomFrame);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::IMAGE_SIZE)->x, thumbnailSize.x, zoomFrame);
				thumbnail->ChangeValueWithAnimation(&thumbnail->GetVectorPointer(VectorType::IMAGE_SIZE)->y, thumbnailSize.y, zoomFrame);
				thumbnailBackGround->ChangeValueWithAnimation(
					&thumbnailBackGround->GetColor(ColorType::INNER)->a, 0, zoomFrame);
				canvases.SetButtomLayer(thumbnailCanvas);
				//layer.SetButtomLayer(thumbnailBackGround);
			}
		}
}

void WorkScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
