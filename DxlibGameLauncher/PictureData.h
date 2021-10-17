#pragma once
#include "DxLib.h"
#include <string>

using namespace std;

struct PictureData
{
	PictureData()
		:handle(0), sizeX(0), sizeY(0)
	{
	};

	string name;

	int handle;

	int sizeX;

	int sizeY;

	bool ExistenceFlag = FALSE;

};

