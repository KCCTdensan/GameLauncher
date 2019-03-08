#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_OTHERSGallery_HPP
#define INCLUDE_OTHERSGallery_HPP


class others_Gallery :public Gallery
{
public:
	others_Gallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~others_Gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif