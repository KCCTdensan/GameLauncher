#pragma once

#include "Gallery.hpp"

#ifndef VIDEO_GALLERY_HPP
#define VIDEO_GALLERY_HPP


class VideoGallery :public Gallery
{
public:
	VideoGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif