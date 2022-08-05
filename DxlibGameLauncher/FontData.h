#pragma once

#include <string>
#include "DxLib.h"

using namespace std;

//#pragma warning(push)
//#pragma warning(disable:26495)

class FontChest
{
public:

	FontChest()
		:size(15),handle(0)
	{}

	string name;

	bool ActiveFlag = FALSE;

	int size;
	int handle;

};

//#pragma warning(pop)