#include "JsonManager.h"
#include <sstream>
#include <fstream>
//#include <iostream>
#include "picojson.h"
//#include <locale>
//#include <codecvt>

#pragma warning(push)
#pragma warning(disable:4834)

using namespace picojson;
using namespace std;

JsonManager::JsonManager()
{
}

int JsonManager::Read(string path)
{
	stringstream ss;
	ifstream fs;
	fs.open(path.c_str(), ios::binary);

	if (!fs.is_open()) {
		return 1;
	}

	ss << fs.rdbuf();
	fs.close();

	picojson::value val;
	ss >> val;
	string err = get_last_error();
	if (!err.empty()) {
		cerr << err << endl;
		return -1;
	}

	object& obj = val.get<object>();

	value::array& TAB = obj["TAB"].get<value::array>();
	
	for (value::array::iterator it = TAB.begin(); it != TAB.end();it++) {
		//GAME
		object& tmp = it->get<object>();
		value::array& APP = tmp["APP"].get<value::array>();
		value::array& GAME = tmp["GAME"].get<value::array>();
		value::array& MODEL = tmp["3DMODEL"].get<value::array>();
		value::array& MUSIC = tmp["MUSIC"].get<value::array>();
		value::array& VIDEO = tmp["VIDEO"].get<value::array>();
		value::array& PICTURE = tmp["PICTURE"].get<value::array>();
		int i = 0;
		for (value::array::iterator it2 = APP.begin(); it2 != APP.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			jsonApp[i].name = name["NAME"].get<string>();
			jsonApp[i].path = name["PATH"].get<string>();
			jsonApp[i].version = name["VERSION"].get<string>();
			jsonApp[i].explanation = name["EXPLANATION"].get<string>();
			jsonApp[i].picPath = name["PICPATH"].get<string>();
			jsonApp[i].guid = name["GUID"].get<string>();

			appMax++;
		}
		if (jsonApp[0].name == "NONE") appMax = 0;
		i = 0;
		for (value::array::iterator it2 = GAME.begin(); it2 != GAME.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			jsonGame[i].name = name["NAME"].get<string>();
			jsonGame[i].path = name["PATH"].get<string>();
			jsonGame[i].version = name["VERSION"].get<string>();
			jsonGame[i].explanation = name["EXPLANATION"].get<string>();
			jsonGame[i].picPath = name["PICPATH"].get<string>();
			jsonGame[i].guid = name["GUID"].get<string>();


			gameMax++;
		}
		if (jsonGame[0].name == "NONE") gameMax = 0;
		i = 0;
		for (value::array::iterator it2 = MODEL.begin(); it2 != MODEL.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			json3DModel[i].name = name["NAME"].get<string>();
			json3DModel[i].path = name["PATH"].get<string>();
			json3DModel[i].version = name["VERSION"].get<string>();
			json3DModel[i].explanation = name["EXPLANATION"].get<string>();
			json3DModel[i].picPath = name["PICPATH"].get<string>();
			json3DModel[i].guid = name["GUID"].get<string>();


			modelMax++;
		}
		if (json3DModel[0].name == "NONE") modelMax = 0;
		i = 0;
		for (value::array::iterator it2 = MUSIC.begin(); it2 != MUSIC.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			jsonMusic[i].name = name["NAME"].get<string>();
			jsonMusic[i].path = name["PATH"].get<string>();
			jsonMusic[i].version = name["VERSION"].get<string>();
			jsonMusic[i].explanation = name["EXPLANATION"].get<string>();
			jsonMusic[i].picPath = name["PICPATH"].get<string>();
			jsonMusic[i].guid = name["GUID"].get<string>();


			musicMax++;
		}
		if (jsonMusic[0].name == "NONE") musicMax = 0;
		i = 0;
		for (value::array::iterator it2 = VIDEO.begin(); it2 != VIDEO.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			jsonVideo[i].name = name["NAME"].get<string>();
			jsonVideo[i].path = name["PATH"].get<string>();
			jsonVideo[i].version = name["VERSION"].get<string>();
			jsonVideo[i].explanation = name["EXPLANATION"].get<string>();
			jsonVideo[i].picPath = name["PICPATH"].get<string>();
			jsonVideo[i].guid = name["GUID"].get<string>();

			videoMax++;
		}
		if (jsonVideo[0].name == "NONE") videoMax = 0;
		i = 0;
		for (value::array::iterator it2 = PICTURE.begin(); it2 != PICTURE.end(); it2++, i++)
		{
			object& name = it2->get<object>();
			jsonPicture[i].name = name["NAME"].get<string>();
			jsonPicture[i].path = name["PATH"].get<string>();
			jsonPicture[i].version = name["VERSION"].get<string>();
			jsonPicture[i].explanation = name["EXPLANATION"].get<string>();
			jsonPicture[i].picPath = name["PICPATH"].get<string>();
			jsonPicture[i].guid = name["GUID"].get<string>();

			pictureMax++;
		}
		if (jsonPicture[0].name == "NONE") pictureMax = 0;
	}
	
	return 0;
}

int JsonManager::Write(SCENE scene, Json jsonData)
{
	return 0;
}

int JsonManager::GetDataNum(SCENE scene)
{
	int num = -1;
	switch (scene)
	{
	case SCENE::TAB_APP:
		num = appMax;
		break;
	case SCENE::TAB_GAME:
		num = gameMax;
		break;
	case SCENE::TAB_MUSIC:
		num = musicMax;
		break;
	case SCENE::TAB_3DMODEL:
		num = modelMax;
		break;
	case SCENE::TAB_VIDEO:
		num = videoMax;
		break;
	case SCENE::TAB_PICTURE:
		num = pictureMax;
		break;
	default:
		break;
	}
	return num;
}

int JsonManager::GetData(SCENE scene, Json* jsonData, int num)
{
	int i = num;
	switch (scene)
	{
	case SCENE::TAB_APP:
		*jsonData = jsonApp[i];
		break;
	case SCENE::TAB_GAME:
		*jsonData = jsonGame[i];
		break;
	case SCENE::TAB_MUSIC:
		*jsonData = jsonMusic[i];
		break;
	case SCENE::TAB_3DMODEL:
		*jsonData = json3DModel[i];
		break;
	case SCENE::TAB_VIDEO:
		*jsonData = jsonVideo[i];
		break;
	case SCENE::TAB_PICTURE:
		*jsonData = jsonPicture[i];
		break;
	default:
		break;
	}
	return 0;
}

#pragma warning(pop)

