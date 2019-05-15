#pragma once

#include "Gallery.hpp"

#ifndef INCLUDE_MODELGallery_HPP
#define INCLUDE_MODELGallery_HPP


class ModelGallery :public Gallery
{
public:
	ModelGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight);
	~ModelGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif