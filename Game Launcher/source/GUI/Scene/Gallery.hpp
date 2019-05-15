#pragma once

#include "scene.hpp"

#ifndef GALLERY_HPP
#define GALLERY_HPP


class Gallery : public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p
	HPEN hPenBkgnd;//�w�i�h��Ԃ��p

public:
	Gallery(HWND hWnd, SceneChangerInterface* sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight);
	~Gallery();
};


#endif