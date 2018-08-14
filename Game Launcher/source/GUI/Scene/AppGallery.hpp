#pragma once

#include "Gallery.hpp"
#include "../../ItemManager.hpp"

#ifndef INCLUDE_APPGALLERY_HPP
#define INCLUDE_APPGALLERY_HPP


class AppGallery :public Gallery
{
	vector<ItemInfo*> Items;

public:
	AppGallery(HWND hWnd, SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~AppGallery();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	int Update(HWND hWnd);
};


#endif