#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_APPGallery_HPP
#define INCLUDE_APPGallery_HPP


class AppGallery :public Gallery
{
public:
	AppGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif