#pragma once
#include <string>
#include "SceneList.h"
#include "JsonFileData.h"
#include "picojson.h"
#include <array>

using namespace std;

#define JSON_MAX 256 

class JsonManager
{
public:
	JsonManager();

	int Read(string path);
	int Write(SCENE scene, Json jsonData);
	int	GetDataNum(SCENE scene);
	int GetData(SCENE scene, Json* jsonData, int num);// numÇÕ0à»è„

private:

	std::array<Json, JSON_MAX>jsonApp;
	std::array<Json, JSON_MAX>jsonGame;
	std::array<Json, JSON_MAX>json3DModel;
	std::array<Json, JSON_MAX>jsonMusic;
	std::array<Json, JSON_MAX>jsonVideo;
	std::array<Json, JSON_MAX>jsonOthers;

	int appMax = 0;
	int gameMax = 0;
	int modelMax = 0;
	int musicMax = 0;
	int videoMax = 0;
	int othersMax = 0;

};

