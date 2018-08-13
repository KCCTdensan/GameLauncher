#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_VIDEOGALLERY_HPP
#define INCLUDE_VIDEOGALLERY_HPP


class VideoGallery :public Gallery
{
public:
	VideoGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~VideoGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif