#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_VIDEOGallery_HPP
#define INCLUDE_VIDEOGallery_HPP


class video_Gallery :public Gallery
{
public:
	video_Gallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~video_Gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif