#pragma once

#include "scene.hpp"

#ifndef INCLUDE_MAINMENU_HPP
#define INCLUDE_MAINMENU_HPP


class MainMenu :public Scene
{
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p

public:
	MainMenu(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight);
	~MainMenu();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int ChangeScene(HWND hWnd, int NextScene);
};


#endif