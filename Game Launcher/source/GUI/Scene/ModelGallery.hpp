#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MODELGallery_HPP
#define INCLUDE_MODELGallery_HPP


class model_Gallery :public Gallery
{
public:
	model_Gallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~model_Gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif