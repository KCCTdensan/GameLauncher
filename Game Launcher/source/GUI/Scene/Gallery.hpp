#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_GALLERY_HPP
#define INCLUDE_GALLERY_HPP


class Gallery :public Scene
{
	const int MenuWidth;

	MemDC MenuDC;
	MemDC PreviewDC;

protected:
	void DrawBkgnd();

public:
	Gallery(SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~Gallery();
};


#endif