#pragma once

#include "Scene.hpp"
#include "../Color.hpp"
#include "contents.hpp"

#ifndef INCLUDE_MAINMENU_HPP
#define INCLUDE_MAINMENU_HPP


class main_menu :public scene
{
	mem_dc *GalleryButtonDCs[MAX_CATEGORY];
	RECT GalleryButtonRects[MAX_CATEGORY];

public:
	main_menu(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~main_menu();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif