#pragma once
//#include "SceneBase.h"

class Header;

struct SharingScenes
{
	Header* header;

	SharingScenes(Header* _header)
		: header(_header) {}

	SharingScenes()
		: header(nullptr) {}
};

