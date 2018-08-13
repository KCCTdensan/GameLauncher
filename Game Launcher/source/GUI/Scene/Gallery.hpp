#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_GALLERY_HPP
#define INCLUDE_GALLERY_HPP


class Gallery :public Scene
{
public:
	Gallery(SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~Gallery();
};


#endif