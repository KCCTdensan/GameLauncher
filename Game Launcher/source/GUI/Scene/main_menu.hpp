#pragma once

#include "scene.hpp"

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP


class MainMenu : public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//背景塗りつぶし用
	HPEN hPenBkgnd;//背景塗りつぶし用

	void drawBackground();

public:
	MainMenu(HWND hWnd, SceneChangerInterface* sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	~MainMenu();
	int initialize();
	int finalize();
	int buttonLUp(unsigned short x, unsigned short y);
	int update();
};


#endif