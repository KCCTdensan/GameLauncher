#pragma once

#include "Gallery.hpp"
#include "../../ItemManager.hpp"

#ifndef INCLUDE_VIDEOGALLERY_HPP
#define INCLUDE_VIDEOGALLERY_HPP


class VideoGallery :public Gallery
{
	vector<ItemInfo*> Items;

public:
	VideoGallery(HWND hWnd, SceneManagerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~VideoGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif