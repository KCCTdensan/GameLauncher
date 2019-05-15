#pragma once

#include "scene.hpp"

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP


class MainMenu : public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p
	HPEN hPenBkgnd;//�w�i�h��Ԃ��p

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