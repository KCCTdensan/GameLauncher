#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_MAINMENU_HPP
#define INCLUDE_MAINMENU_HPP


class MainMenu :public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p
	HPEN hPenBkgnd;//�w�i�h��Ԃ��p

public:
	MainMenu(HWND hWnd, SceneChangerInterface* SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~MainMenu();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif