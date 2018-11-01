#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_VIDEOGALLERY_HPP
#define INCLUDE_VIDEOGALLERY_HPP


class video_gallery :public gallery
{
public:
	video_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~video_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif