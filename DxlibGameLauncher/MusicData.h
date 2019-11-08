#pragma once
#include "DxLib.h"
#include <string>

using namespace std;

struct MusicData
{
	MusicData()
		:handle(0),startPosition(0),range(0)
	{
	};

	string name;

	int handle;

	int startPosition;

	int range;

	bool ExistenceFlag = FALSE;

};

