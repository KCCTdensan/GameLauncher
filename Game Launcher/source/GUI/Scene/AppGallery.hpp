#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_APPGALLERY_HPP
#define INCLUDE_APPGALLERY_HPP


class app_gallery :public gallery
{
public:
	app_gallery(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~app_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif