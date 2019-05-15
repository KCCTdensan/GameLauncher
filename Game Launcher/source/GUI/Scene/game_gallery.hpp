#pragma once

#include "Gallery.hpp"

#ifndef GAME_GALLERY_HPP
#define GAME_GALLERY_HPP


class GameGallery :public Gallery
{
public:
	GameGallery(HWND hWnd, SceneChangerInterface* sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif