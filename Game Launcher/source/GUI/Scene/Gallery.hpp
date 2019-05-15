#pragma once

#include "scene.hpp"

#ifndef GALLERY_HPP
#define GALLERY_HPP


class Gallery : public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//背景塗りつぶし用
	HPEN hPenBkgnd;//背景塗りつぶし用

public:
	Gallery(HWND hWnd, SceneChangerInterface* sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	~Gallery();
};


#endif