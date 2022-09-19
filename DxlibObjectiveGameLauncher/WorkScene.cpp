#include "WorkScene.h"

WorkScene::WorkScene()
{}

WorkScene::WorkScene(SharingScenes* _sharingScenes, std::string workGuid)
	: SceneBase(_sharingScenes), guid(workGuid),
	canvas(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true),
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y))
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

	if ((int)lists.size() == i) {
		printfDx("Not Found : %s\n", guid.c_str());
	}
	else {
		printfDx("%s\n", lists[i].get<picojson::object>()["GUID"].get<std::string>().c_str());
		this->obj = lists[i].get<picojson::object>(); // 保存
	}

	std::string thumbnailName = "Thumb:" + this->obj["GUID"].get<std::string>();
	std::string thumbnailPath = this->obj["Directory"].get<std::string>() + this->obj["Thumbnail"].get<std::string>();

	ImageChest::CreateImageHandle(thumbnailName, thumbnailPath);
	int handle = ImageChest::GetImageHandle(thumbnailName);
	thumbnail = ImageObject(
		PosVec(150.f, ApplicationPreference::startScenePos + 150.f),
		PosVec(300, 300),
		ImageChest::GetImageHandle(thumbnailName), true, true);
	thumbnail.SetImageSize(PosVec(300, 300));
	thumbnail.SetImageTurnFlag(false, false);
	thumbnail.SetOutlineColor(ColorPreset::tileOuterMouse, 3.f);


	layer.AddObject(&thumbnail);
}

void WorkScene::Collide()
{
	canvases.Collide();
	layer.Collide();

	/****************/

	/****************/

	layer.Update();
	canvases.Update();
}

void WorkScene::Update()
{
	RegFonts();
}

void WorkScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
