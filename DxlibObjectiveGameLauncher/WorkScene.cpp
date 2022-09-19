#include "WorkScene.h"

WorkScene::WorkScene()
{}

WorkScene::WorkScene(SharingScenes* _sharingScenes, std::string workGuid)
	: SceneBase(_sharingScenes), guid(workGuid),
	canvas(PosVec(0.f, ApplicationPreference::startScenePos), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y - ApplicationPreference::startScenePos), true),
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y))
{
	/********** JSON ì«çû ***********/

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

	/******** JSON ì«çûèIóπ *********/

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
	}
}

void WorkScene::Collide()
{
}

void WorkScene::Update()
{
}

void WorkScene::Draw()
{
}
