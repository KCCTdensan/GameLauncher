#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MUSICGALLERY_HPP
#define INCLUDE_MUSICGALLERY_HPP


class music_gallery :public gallery
{
public:
	music_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~music_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif