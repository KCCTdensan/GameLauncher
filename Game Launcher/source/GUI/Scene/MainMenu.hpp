#pragma once

#include "Scene.hpp"
#include "../Color.hpp"
#include "contents.hpp"

#ifndef INCLUDE_MAINMENU_HPP
#define INCLUDE_MAINMENU_HPP


class MainMenu :public Scene
{
	MemDC *GalleryButtonDCs[MAX_CATEGORY];
	RECT GalleryButtonRects[MAX_CATEGORY];

public:
	MainMenu(HWND hWnd, SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~MainMenu();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif