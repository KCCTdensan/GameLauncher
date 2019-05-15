#pragma once

#include "Gallery.hpp"

#ifndef OTHERS_GALLERY_HPP
#define OTHERS_GALLERY_HPP


class OthersGallery :public Gallery
{
public:
	OthersGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif