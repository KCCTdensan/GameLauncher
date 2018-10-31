#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MODELGALLERY_HPP
#define INCLUDE_MODELGALLERY_HPP


class model_gallery :public gallery
{
public:
	model_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~model_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif