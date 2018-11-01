#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_OTHERSGALLERY_HPP
#define INCLUDE_OTHERSGALLERY_HPP


class others_gallery :public gallery
{
public:
	others_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~others_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif