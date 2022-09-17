#pragma once
//#include "SceneBase.h"

class Header;
class PopupScene;

struct SharingScenes
{
	Header* header;
	PopupScene* popupScene;

	SharingScenes(Header* _header, PopupScene* _popupScene)
		: header(_header), popupScene(_popupScene) {}

	SharingScenes()
		: header(nullptr), popupScene(nullptr) {}
};

