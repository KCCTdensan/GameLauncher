#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MUSICGallery_HPP
#define INCLUDE_MUSICGallery_HPP


class MusicGallery :public Gallery
{
public:
	MusicGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~MusicGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif