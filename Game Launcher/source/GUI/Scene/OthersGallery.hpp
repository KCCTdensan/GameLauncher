#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_OTHERSGallery_HPP
#define INCLUDE_OTHERSGallery_HPP


class OthersGallery :public Gallery
{
public:
	OthersGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~OthersGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif