#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_GAMEGALLERY_HPP
#define INCLUDE_GAMEGALLERY_HPP


class GameGallery :public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//”wŒi“h‚è‚Â‚Ô‚µ—p
	HPEN hPenBkgnd;//”wŒi“h‚è‚Â‚Ô‚µ—p

public:
	GameGallery(HWND hWnd, SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif