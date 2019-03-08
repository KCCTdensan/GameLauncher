#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_PICTUREGallery_HPP
#define INCLUDE_PICTUREGallery_HPP


class picture_Gallery :public Gallery
{
public:
	picture_Gallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~picture_Gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif