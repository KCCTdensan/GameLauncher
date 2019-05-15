#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MODELGallery_HPP
#define INCLUDE_MODELGallery_HPP


class ModelGallery :public Gallery
{
public:
	ModelGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y, unsigned int param);
	int update();
};


#endif