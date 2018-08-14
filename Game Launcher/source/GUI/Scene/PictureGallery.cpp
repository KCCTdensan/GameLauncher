#include "PictureGallery.hpp"


PictureGallery::PictureGallery(HWND hWnd, SceneManagerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
{
	Items = ItemManager::GetItems(CAT_PICTURE);
}

PictureGallery::~PictureGallery()
{

}

int PictureGallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int PictureGallery::Finalize(HWND hWnd)
{
	return 0;
}

int PictureGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int PictureGallery::Update(HWND hWnd)
{
	return 0;
}