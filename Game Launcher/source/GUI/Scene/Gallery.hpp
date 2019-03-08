#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_Gallery_HPP
#define INCLUDE_Gallery_HPP


class Gallery : public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p
	HPEN hPenBkgnd;//�w�i�h��Ԃ��p

public:
	Gallery(SceneChangerInterface* SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~Gallery();
};


#endif