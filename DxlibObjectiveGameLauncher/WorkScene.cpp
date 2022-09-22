#include "WorkScene.h"
#include "Header.h"

WorkScene::WorkScene()
	: descriptionCanvas(nullptr), thumbnailCanvas(nullptr),
	canvas(nullptr), bg(nullptr),
	thumbnail(nullptr), category(nullptr), title(nullptr), author(nullptr), guidText(nullptr), description(nullptr), descriptionLines(),
	launch(nullptr),
	imagesCanvas(nullptr), isBigCanvas(nullptr), isBigImage(nullptr), isBigPos(nullptr), isBigSize(nullptr), photoGalleryText(nullptr),
	imageBackGround(nullptr)
{}

WorkScene::WorkScene(SharingScenes* _sharingScenes, std::string workGuid)
	: SceneBase(_sharingScenes), guid(workGuid),
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

		i = 0;
		float maxImageLongLength = 300.f; // 最大幅 どちらかの幅が300になる

		for (auto& item : this->obj["Images"].get<picojson::array>()) {
			// printfDx("%s\n", item.get<picojson::object>()["FilePath"].get<std::string>().c_str());
			std::string imageName = "Image" + std::to_string(i) + ":" + this->obj["GUID"].get<std::string>();
			std::string imagePath = this->obj["Directory"].get<std::string>() + item.get<picojson::object>()["FilePath"].get<std::string>();

			ImageChest::CreateImageHandle(imageName, imagePath);
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
		//category->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// 初期位置 +50
		title = new TextObject(
			PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 50.f), PosVec(),
			"smart50", this->obj["TitleName"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		//title->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// +100
		author = new TextObject(
			PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 100.f), PosVec(),
			"smart25", this->obj["Author"].get<std::string>(), ColorPreset::textBlack, TextAlign::LEFT, false);
		//author->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

		// +125
		guidText = new TextObject(
			PosVec(75.f + maxThumbnailLongLength, ApplicationPreference::startScenePos + 125.f), PosVec(),
			"smart25", this->obj["GUID"].get<std::string>(), ColorPreset::textGray, TextAlign::LEFT, false);
		//guidText->SetMaxWidth((int)(ApplicationPreference::GetBackgroundSize().x - 100.f - maxImageLongLength));

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

		layer.AddObject(launch);

		canvases.AddObject(canvas);
		canvases.AddObject(imagesCanvas);
		canvases.AddObject(thumbnailCanvas);
		canvases.AddObject(descriptionCanvas);
	}

	// フォント追加
	fonts.push_back(FontHandle("smart80", "03スマートフォントUI", 80, 15));
	fonts.push_back(FontHandle("smart50", "03スマートフォントUI", 50, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
	fonts.push_back(FontHandle("smart25", "03スマートフォントUI", 25, 15));
}

void WorkScene::Collide()
{
	canvases.Collide();
	layer.Collide();
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
			descriptionCanvas->SetArea(PosVec(0, textHeight), (float)description->GetFontHeight() * 2.f / textHeight);
		}

	if (launch != nullptr) {
		launch->GetTextObject()->SetPos(launch->GetPos());
		launch->GetTextObject()->Move(PosVec(
			(thumbnailSize.x - launch->GetTextObject()->GetTextWidth()) / 2.f,
			(150.f - launch->GetTextObject()->GetTextHeight()) / 2.f));

	}

	sharingScenes->header->SetSubtitle(this->obj["TitleName"].get<std::string>());

	if (launch != nullptr)
		if (launch->GetMouseSelected()) {
			// 押下時の処理をここに
			launch->SetMouseOff();
			std::string exePath = this->obj["Directory"].get<std::string>() + this->obj["FilePath"].get<std::string>();
			ShellExecute(NULL, "open", exePath.c_str(), NULL, NULL, 0);
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

void WorkScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
