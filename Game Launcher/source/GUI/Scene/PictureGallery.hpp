#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_PICTUREGALLERY_HPP
#define INCLUDE_PICTUREGALLERY_HPP


class PictureGallery :public Gallery
{
public:
	PictureGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~PictureGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif