#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_PICTUREGALLERY_HPP
#define INCLUDE_PICTUREGALLERY_HPP


class picture_gallery :public gallery
{
public:
	picture_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~picture_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif