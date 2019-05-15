#pragma once

#include "Gallery.hpp"

#ifndef PICTURE_GALLERY_HPP
#define PICTURE_GALLERY_HPP


class PictureGallery :public Gallery
{
public:
	PictureGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif