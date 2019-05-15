#pragma once

#include "Gallery.hpp"

#ifndef MUSIC_GALLERY_HPP
#define MUSIC_GALLERY_HPP


class MusicGallery :public Gallery
{
public:
	MusicGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif