#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_GAMEGALLERY_HPP
#define INCLUDE_GAMEGALLERY_HPP


class game_gallery :public gallery
{
public:
	game_gallery(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~game_gallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif