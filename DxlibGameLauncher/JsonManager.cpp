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

int JsonManager::Read(wstring path)
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
		value::array& VIDEO = tmp["OTHERS"].get<value::array>();
		value::array& OTHERS = tmp["VIDEO"].get<value::array>();
		int i = 0;
		for (value::array::iterator it2 = APP.begin(); it2 != APP.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			jsonApp[i].name = name["NAME"].get<wstring>();
			jsonApp[i].path = name["PATH"].get<wstring>();
			jsonApp[i].version = name["VERSION"].get<wstring>();
			jsonApp[i].explanation = name["EXPLANATION"].get<wstring>();

			appMax++;
		}
		i = 0;
		for (value::array::iterator it2 = GAME.begin(); it2 != GAME.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			jsonGame[i].name = name["NAME"].get<wstring>();
			jsonGame[i].path = name["PATH"].get<wstring>();
			jsonGame[i].version = name["VERSION"].get<wstring>();
			jsonGame[i].explanation = name["EXPLANATION"].get<wstring>();

			gameMax++;
		}
		i = 0;
		for (value::array::iterator it2 = MODEL.begin(); it2 != MODEL.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			json3DModel[i].name = name["NAME"].get<wstring>();
			json3DModel[i].path = name["PATH"].get<wstring>();
			json3DModel[i].version = name["VERSION"].get<wstring>();
			json3DModel[i].explanation = name["EXPLANATION"].get<wstring>();

			modelMax++;
		}
		i = 0;
		for (value::array::iterator it2 = MUSIC.begin(); it2 != MUSIC.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			jsonMusic[i].name = name["NAME"].get<wstring>();
			jsonMusic[i].path = name["PATH"].get<wstring>();
			jsonMusic[i].version = name["VERSION"].get<wstring>();
			jsonMusic[i].explanation = name["EXPLANATION"].get<wstring>();

			musicMax++;
		}
		i = 0;
		for (value::array::iterator it2 = VIDEO.begin(); it2 != VIDEO.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			jsonVideo[i].name = name["NAME"].get<wstring>();
			jsonVideo[i].path = name["PATH"].get<wstring>();
			jsonVideo[i].version = name["VERSION"].get<wstring>();
			jsonVideo[i].explanation = name["EXPLANATION"].get<wstring>();

			videoMax++;
		}
		i = 0;
		for (value::array::iterator it2 = OTHERS.begin(); it2 != OTHERS.end(), i < JSON_MAX; it2++, i++)
		{
			object& name = it2->get<object>();
			jsonOthers[i].name = name["NAME"].get<wstring>();
			jsonOthers[i].path = name["PATH"].get<wstring>();
			jsonOthers[i].version = name["VERSION"].get<wstring>();
			jsonOthers[i].explanation = name["EXPLANATION"].get<wstring>();

			othersMax++;
		}
	}
	
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
	case SCENE::TAB_OTHERS:
		num = othersMax;
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
		jsonData = &jsonApp[i];
		break;
	case SCENE::TAB_GAME:
		jsonData = &jsonGame[i];
		break;
	case SCENE::TAB_MUSIC:
		jsonData = &jsonMusic[i];
		break;
	case SCENE::TAB_3DMODEL:
		jsonData = &json3DModel[i];
		break;
	case SCENE::TAB_VIDEO:
		jsonData = &jsonVideo[i];
		break;
	case SCENE::TAB_OTHERS:
		jsonData = &jsonOthers[i];
		break;
	default:
		break;
	}
	return 0;
}

#pragma warning(pop)

