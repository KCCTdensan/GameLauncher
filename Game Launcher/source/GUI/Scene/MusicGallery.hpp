#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MUSICGALLERY_HPP
#define INCLUDE_MUSICGALLERY_HPP


class MusicGallery :public Gallery
{
public:
	MusicGallery(HWND hWnd, SceneManagerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~MusicGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif